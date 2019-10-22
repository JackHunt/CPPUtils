#include <string>
#include <CPPUtils/IO/CSVFile.hpp>

using CPPUtils::IO::CSVFile;
using CSV = CSVFile<float, int>;

int main() {
    // Make two empty CSV files.
    CSV csvA, csvB;

    // Make a string of parseable types and add to the file.
    const auto a = "3.14, True, 2, 6.28, abc";
    csvA.appendRow(a);

    // Same again.
    const auto b = "6.28, False, -2, 3.14, cba";
    csvB.appendRow(b);

    // Write files out.
    csvA.writeToDisk("a.csv");
    csvB.writeToDisk("b.csv");

    // Create new CSVFile and read in the files.
    CSV c;
    c.readFromDisk("a.csv");
    c.readFromDisk("b.csv");

    // Write out new combined CSV.
    const auto lines = c.getDataString();
    for (const auto &line : lines) {
        std::cout << line << std::endl;
    }
    c.writeToDisk("c.csv");

    // Get numeric types only and print.
    const auto numericRows = c.getDataNumeric();
    for (const auto &row : numericRows) {
        for (auto v : row) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    std::getchar();
    return 0;
}