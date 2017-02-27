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

    int predic      = mySVM.predictLabel(coefs);
