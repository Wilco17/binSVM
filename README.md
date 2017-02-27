# binSVM

C++ binary SVM classifier

# DESCRIPTION

This software implements SVMClassifier class: a SVMClassifier object performs binary classification with a given SVM classifier.

This software DOES NOT TRAIN SVM classifiers.

SVM Classifier is given in a INI file "SVM.INI"

VERSION 1.0 = ONLY GAUSSIAN KERNEL IS IMPLEMENTED

# USAGE

Create SVMClassifier object:

    string          svmIniFile                      =   "SVM.ini";
    SVMclassifier   mySVM(svmIniFile);
    
Use predictLabel method to obtain predicted class:

    vector<double>    featrues(X) ={...};
    int predic      = mySVM.predictLabel(features);
    
Classes:

        class SVMclassifier {...
        
        public:
        SVMclassifier(string config_file);      /** Constructor **/
        }
   
Public methods:
        
     vector<vector<double>>    getVectors(void);  /** Get supoort vectors **/
     double                    getBias(void);     /** Get classification bias **/
     vector<double>            getMu(void);       /** Get mean of vectors (for scaling purposes) **/
     vector<double>            getSigma(void);    /** Get std. deviation (for scaling purposes) **/
     int                       predictLabel(vector<double> features); /** Perform classification **/
 
# INSTALLATION

Add /include/binSVM.h and binSVM.cpp to your project and link them properly

IMPORTANT:

This software uses SimpleIni to read the INI file, so you have to install it: https://github.com/brofield/simpleini
