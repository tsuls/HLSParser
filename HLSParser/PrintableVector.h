//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_PRINTABLEVECTOR_H
#define HLSPARSER_PRINTABLEVECTOR_H


#include <vector>
#include <ostream>
#include <iostream>
/*
 * Wrapper class for vector to globally override << operator.
 * This could have more functions, but for the sake of this assignment,
 * we will just have push_back and a getter for other vector functions.
 */

//Template use for generics
template<typename T>
class PrintableVector{
private:
    std::vector<T> _v;
public:
    PrintableVector() {

    }

    explicit PrintableVector(const std::vector<T>& _nv) {
        _v = _nv;
    }

    void push_back(T element){
        _v.push_back(element);
    }

    std::vector<T> &getV()  {
        return _v;
    }

    //operator << override to print the underlying vector.
    friend std::ostream& operator<< (std::ostream &os, const PrintableVector<T>& vector){

        //copy the vector to an output stream iterator, use cout.

        //However, if it's a nested list, comma separate it
        if(typeid(T).name() == typeid(std::string).name()) {
            std::copy(vector._v.begin(), vector._v.end() - 1,
                      std::ostream_iterator<T>(std::cout, ","));

            //skip the comma at the end of the stream
            std::copy(vector._v.end() - 1, vector._v.end(),
                      std::ostream_iterator<T>(std::cout));
        }
        else{ //just pring
            std::copy(vector._v.begin(), vector._v.end(),
                      std::ostream_iterator<T>(std::cout));
        }

        return os;
    };

};


#endif //HLSPARSER_PRINTABLEVECTOR_H
