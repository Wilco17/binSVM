# binSVM

C++ binary SVM classifier

# DESCRIPTION

This software implements SVMClassifier class: a SVMClassifier object performs binary classification with a given SVM classifier.

This software DOES NOT TRAIN SVM classifiers.

SVM Classifier is given in a INI file:

    SVM.INI: This classifier was randomly generated for explanation purposes

VERSION 1.0 = ONLY GAUSSIAN KERNEL IS IMPLEMENTED (CONTRIBUTIONS FOR OTHER KERNELS WILL BE NICELY RECEIVED)

# USAGE

Create SVMClassifier object:

    string          svmIniFile                      =   "SVM.ini";
    SVMclassifier   mySVM(svmIniFile);
    
Use predictLabel method to obtain predicted class:

    vector<double>    featrues(X) ={...};
    int predic      = mySVM.predictLabel(features);
    
NOTE: features vector dimension has to be consistent with the INI configuration file of the SVM classifier

Class:

        class SVMclassifier {...
        
        public:
        SVMclassifier(string config_file);      /** Constructor **/
        }
   
Public methods:
        
     vector<vector<double>>    getVectors(void);  /** Get supoort vectors **/
     double                    getBias(void);     /** Get classification bias **/
     vector<double>            getMu(void);       /** Get mean of supported vectors (for scaling purposes) **/
     vector<double>            getSigma(void);    /** Get std. deviation of supported vectors (for scaling purposes) **/
     int                       predictLabel(vector<double> features); /** Perform classification (1,0) **/
 
# INSTALLATION

Add /include/binSVM.h and binSVM.cpp to your project and link them properly

IMPORTANT:

This software uses SimpleIni to read the INI file, so you have to install it: https://github.com/brofield/simpleini

# CONTACT

Any issues, commentaries or contributions are well received in jaureguinovo@gmail.com or ignaciojauregui@gts.uvigo.es
