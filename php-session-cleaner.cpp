#include <iostream>
#include <string>
#include <ctime>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    path p(argc > 1 ? argv[1] : ".");
    int minDays = 30; // can be also taken from the arguments

    if(is_directory(p)) {
        std::cout << p << " contains the following:\n\n";
        std::time_t timeNow = time(0);
        int seconds_in_a_day = 60 * 60 * 24;
        int removed = 0;

        for(auto& entry : boost::make_iterator_range(directory_iterator(p), {})) {
            if (!is_directory(entry)) {
                std::string path = entry.path().filename().string();
                if (path.find("sess_") == 0) {
                    // boost::system::error_code ecSize;
                    // boost::uintmax_t filesize = file_size(entry, ecSize);
                    boost::system::error_code ecTime;
                    std::time_t tm = last_write_time(entry, ecTime);
                    double days = difftime(timeNow, tm) / seconds_in_a_day;
                    if (days > minDays) {
                         remove(path);
                         std::cout << path << " removed, modified " << days << " days ago\n";
                         removed ++;
                    }			 
                }
            }
        }
        std::cout << removed << " files removed\n";
    } else {
        std::cout << p << " not a folder\n";
    }
}
