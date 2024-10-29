/*
    This works pretty well. Rename and promote!
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

// the threshold is the number of elements to average
// meanVector is an array to hold those elements
// fileName is the name of a text value that holds the standard deviation values in the form
// index, content

// don't change counter!
static double threshold = 1000; 
std::vector<double> meanVector;
static int counter = 0;
std::string fileName = "example.txt";

// each time a line is read in, this function should be executed.
// averages batches of numbers, as well as the last (probably) partial batch
void processData(int index, double content) {
    // for printing each LINE of of the file to the screen
    // std::cout << index << " " << counter << " " << content << '\n';
    meanVector.push_back(content);
    counter++;
    // index is -1 when EOF is reached.
    if( counter % int(threshold) == 0 || index == -1 ) {
        // find mean of values in the vector
        double sumElements = std::accumulate(meanVector.begin(), meanVector.end(), 0.0);
        double meanValue = sumElements / counter;
        // double meanValue = sumElements / threshold;
        std::cout << meanValue << std::endl;
        meanVector = {};

        // output the number of lines averaged to check we are getting the last, partial batch
        // std::cout << "counter = " << counter << std::endl;

        // reset the counter, so that the last batch gets averaged in too.
        counter = 0;
    }
}

int main () {
    std::cout << "*******************************************" << std::endl;
    std::cout << "This takes the file " << fileName << " as input," << std::endl;
    std::cout << "and averages " << threshold << " lines together " << std::endl;
    std::cout << "before returning the mean value." << std::endl;
    std::cout << "*******************************************" << std::endl;
    std::ifstream myfile;
    // put filename here -- now handled by a string variable
    myfile.open(fileName);
    std::string myline;
    if ( myfile.is_open() ) {
        while ( myfile ) {
            std::getline (myfile, myline);
            std::string thisLine = myline;
            // get the position of "," in str
            std::size_t pos = thisLine.find(",");
            // move the marker two positions ahead to account for comma and space
            // get from "," to the end
            std::string strContent = thisLine.substr(pos+2);
            double content = stod(strContent);
            std::string strIndex = thisLine.substr(0, pos);
            int index = stoi(strIndex);
            processData(index,content);
            // throw a flag if EOF is reached...
            if( myfile.peek() == EOF ) processData(-1,content);
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }
    return 0;
}