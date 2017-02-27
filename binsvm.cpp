#include "include/binSVM.h"
using namespace std;

ostream& operator<<(std::ostream& out,const SVMclassifier& c){
       cout <<"----------------------------------------------------"<<endl;
       cout <<"[General]"<<endl;
       cout << "type \t\t=\tSVM-"<<c.kernelType<<endl;
       cout << "numVectors \t=\t"<<c.numVectors<<endl;
       cout << "numFeatures \t=\t"<<c.numFeatures<<endl;
       cout << "numClasses \t=\t"<<c.numClasses<<endl;
       cout << "classLoss \t=\t"<<(double)c.classLoss<<endl;
       return out;
       };
SVMclassifier::SVMclassifier(string config_file) {
    CSimpleIniA         ini(true,false,false);
    ini.LoadFile(config_file.c_str()) < 0 ? cout << "Can't load SVM-object config. file\n" : cout << "SVM-object config. file loaded \n";


    this -> kernelType  =   ini.GetValue("General","type",NULL);
    this -> numVectors  =   stoi(ini.GetValue("General","numVectors",NULL));
    this -> numFeatures =   stoi(ini.GetValue("General","numFeatures",NULL));
    this -> numClasses  =   stoi(ini.GetValue("General","numClasses",NULL));
    this -> classNames  =   ini.GetValue("General","classNames",NULL);
    this -> classLoss   =   stod(ini.GetValue("General","classLoss",NULL));
    this->scale         =   stod(ini.GetValue("Prediction_params","scale",NULL));
    this->bias          =   stod(ini.GetValue("Prediction_params","bias",NULL));
    this->castString2Vector<double>(ini.GetValue("Prediction_params","mu",NULL),this->mu,true,',');
    this->castString2Vector<double>(ini.GetValue("Prediction_params","sigma",NULL),this->sigma,true,',');
    this->castString2Vector<double>(ini.GetValue("Prediction_params","alpha",NULL),this->alpha,true,';');
    this->castString2Array<double>(ini.GetValue("Prediction_params","supportVectors",NULL),this->supportVectors,true,';',',');
    this->castString2Vector<double>(ini.GetValue("Prediction_params","supportLabels",NULL),this->supportLabels,true,';');

};
vector<vector<double>> SVMclassifier::getVectors(void) {
  return SVMclassifier::supportVectors;
};

double SVMclassifier::getBias( void ) {
   return SVMclassifier::bias;
};
vector<double> SVMclassifier::getMu( void ) {
   return SVMclassifier::mu;
};

vector<double> SVMclassifier::getSigma( void ) {
   return SVMclassifier::sigma;
};
int SVMclassifier::predictLabel(vector<double> features){

    int kernel_len = this->numVectors;
    double  sum = 0.0;

    const string gauss      =   "gaussian";
    const string linear     =   "linear";
    const string poly       =   "polynomial";

    #ifdef SVM_USE_OMP
    #pragma omp parallel for
    #endif
    for (int jj=0;jj<kernel_len;jj++){
        double kernel_func=1.0;
        for (int hh=0;hh<this->numFeatures;hh++){
            double std_features  = (features[static_cast<size_t>(hh)] - (this->mu)[static_cast<size_t>(hh)])/(this->sigma)[static_cast<size_t>(hh)];
            if((this->kernelType).compare(gauss)){
               kernel_func = kernel_func*exp(-(std_features- this->supportVectors[static_cast<size_t>(hh)][static_cast<size_t>(jj)])*(std_features - this->supportVectors[static_cast<size_t>(hh)][static_cast<size_t>(jj)])*(1/this->scale)*(1/this->scale));
            }
        }
        sum+=this->alpha[static_cast<size_t>(jj)]*this->supportLabels[static_cast<size_t>(jj)]*kernel_func;
    }
    int label;
    sum + this->bias >= 0 ? label = 1 : label = 0;
    return label;
};



