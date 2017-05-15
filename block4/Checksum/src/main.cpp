#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "ArgumentsParser.h"
#include "Checksum.h"
#include "ManifestReader.h"
#include "ManifestWriter.h"

namespace {
    void print_help() {
        std::cout << "Usage: checksum --calc [<file_names>...] or --check <manifest_name>" << std::endl;
    }

    void print_command_line_error() {
        std::cerr << "Error: incorrect command line" << std::endl;
        print_help();
    }

    std::string get_date_str() {
        time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string date = std::ctime(&time);
        std::replace(date.begin(), date.end(), ' ', '_');
        std::replace(date.begin(), date.end(), ':', '_');
        return date;
    }

    void process_calc(const std::vector<std::pair<Key, Values>> &args) {
        Manifest manifest;
        for (const auto &f : args[0].second) {
            std::ifstream is(f);
            if (!is) {
                std::cerr << "Failed to open file " << f << std::endl;
                continue;
            }
            uint16_t checksum;
            if (!Checksum::calc_crc16(is, checksum)) {
                std::cerr << "Failed to calculate checksum for file " << f << std::endl;
                continue;
            }
            manifest.push_back(std::make_pair(f, checksum));
        }
        std::ofstream os("manifest_" + get_date_str());
        if (!ManifestWriter::write(os, manifest)) {
            std::cerr << "Failed to write file-manifest" << std::endl;
        }
    }

    void process_check(const std::vector<std::pair<Key, Values>> &args) {
        // Only one file-manifest supported
        if (args[0].second.size() != 1) {
            print_command_line_error();
            return;
        }

        std::ifstream manifest(args[0].second[0]);
        if (!manifest) {
            std::cerr << "Failed to open file-manifest" << std::endl;
            return;
        }

        Manifest files_to_check;
        if (!ManifestReader::read(manifest, files_to_check)) {
            std::cerr << "Failed to read file-manifest" << std::endl;
            return;
        }

        for (const auto &to_check : files_to_check) {
            std::ifstream is(to_check.first);
            if (!is) {
                std::cerr << "Failed to open file " << to_check.first << std::endl;
                continue;
            }
            std::cout << to_check.first << ":" << std::boolalpha
                      << Checksum::check_crc16(is, static_cast<uint16_t>(to_check.second))
                      << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    constexpr const char Calc[] = "--calc";
    constexpr const char Check[] = "--check";

    ArgumentsParser argumentsParser({Calc, Check});
    std::stringstream ss;
    if (argc >= 1) {
        ss << argv[0];
    }
    for(int i = 1; i < argc; ++i) {
        ss << ' ' << argv[i];
    }
    const std::vector<std::pair<Key, Values>> args = argumentsParser.parse(ss);

    // Must be only one command
    if (args.size() != 1) {
        print_command_line_error();
        return 0;
    }

    if (args[0].first == Calc) {
        process_calc(args);
    } else if (args[0].first == Check){
        process_check(args);
    } else {
        print_command_line_error();
    }
    return 0;
}