/*  Copyright (c) 2017 - Ignacio Jáuregui Novo
 *  Multimedia Technologies Group. University of Vigo, Spain
 *  email: ignaciojauregui@gts.uvigo.es
 *
 *  This piece of code is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *  SimpleIni.h Copyright. MIT License
 *
 *  Copyright (c) 2006-2012, Brodie Thiesfield
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is furnished
 *  to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 *  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 *  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef MYSVM_H
#define MYSVM_H
#include <QCoreApplication>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <SimpleIni.h>
#include <iterator>
#include <type_traits>
#define SVM_USE_OMP
using namespace std;
class SVMclassifier {
   private:
      //General info.
      string                    kernelType  = "gaussian";
      short                     numVectors  = 0;
      short                     numFeatures = 0;
      short                     numClasses  = 0;
      string                    classNames;
      double                    classLoss  =  0.0;
      //Prediction params.
      vector<vector<double>>    supportVectors;             //numClasses-by-numVectors matrix
      double                    bias;
      vector<double>            alpha;
      vector<double>            mu;
      vector<double>            sigma;
      vector<double>            supportLabels;
      double                    scale;
      /** TEMPLATES **/
      template <typename T>
      void castString2Vector (string s, vector<T>& v, bool brackets, char separator)
      {
        //Removing initial and final brackets
          if(brackets)
          {
            s.erase(s.begin());
            s.erase(s.end());
          }
        //Casting
          std::stringstream ss;
          ss.str(s);
          std::string item;
          while (std::getline(ss, item, separator))
          {
              if(is_same<T,double>::value)
                 v.push_back(stod(item));
              if (is_same<T,int>::value)
                 v.push_back(stoi(item));
          }

      }
      template <typename T>
      void castString2Array (string s, vector<vector<T>>& v, bool brackets, char separator1, char separator2)
      {
        //Removing initial and final brackets
          if(brackets){
            s.erase(s.begin());
            s.erase(s.end());
          }
       //Casting
          std::stringstream ss;
          ss.str(s);
          std::string item;
          while (std::getline(ss, item, separator1))
          {
              if(is_same<T,double>::value)
              {
                   vector<double> aux_v;
                   castString2Vector<double>(item,aux_v,false,separator2);
                   v.push_back(aux_v);
              }
          }
       }
public:
     vector<vector<double>>    getVectors(void);
     double                    getBias(void);
     vector<double>            getMu(void);
     vector<double>            getSigma(void);
     int                       predictLabel(vector<double> features);
     SVMclassifier(string config_file);
     friend ostream& operator<<(ostream& out, const SVMclassifier& c);
};
#endif // MYSVM_H
