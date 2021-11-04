# MNXB01-project
Repo for the final project of the MNXB01 course at Lund University. Autumn 2021.

**Group H**

: Ennio Mara, Jesper Larsson and Antton Lamarca

## Usage

The 'rootlogon.C' file makes it so that the main 'project.cpp' file and the 'src/tempTrender.cpp' file
are compiled automatically with just starting ROOT.
(Make sure to include the local path to your 'include/' directory in the 'rootlogon.C' file for it to work!).

In order to use the implemented functions, you can either run the 'project()' function directly:

    root
    project()

Or create a tempTrender object and call the specific member functions you are interested in with the desired inputs:

    root
    tempTrender* test_2 = new tempTrender("../datasets/smhi-opendata_1_162870_20210926_101011_Lulea.csv")
    test_2->tempOnDay(1,2)

Note that we avoided uploading the data to GitHub, but you will of course need to include the local path to the file of interest in your 'project.cpp' file for ``` project() ``` to work.

## Contents

The structure of the project is simple:

You can find information about the development steps of the project in the 'ChangeLog.txt' file.

All the code is stored in the 'code/' directory. It contains the main 'project.cpp' file as well as the 'rootlogon.C' file.
The 'code/src/' directory contains the 'tempTrender.cpp' file, which has code for three of the proposed example graphs and an original graph that calculates the mean yearly temperature for a city in a given range of years.
The 'measurement.cpp' file contains code for another original graph that calculates total yearly averages from monthly averages.
The header files for both are stored in 'code/include/'.

## Workplan

Broadly speaking, the separation of tasks was the following:
* Ennio worked on the yearly average graph produced by 'measurement.cpp'.
* Jesper worked on the ``` tempMeanYearly() ``` member function of 'tempTrender.cpp'.
* Antton worked on the non-original member functions of 'tempTrender.cpp': both versions of ``` tempOnDay() ```, and ``` tempPerDay() ```.
