# MNXB01-project
Repo for the final project of the MNXB01 course at Lund University. Autumn 2021.

Group H
	Jesper Larsson
	Antton Lamarca

##Usage

The 'rootlogon.C' file makes it so that the main 'project.cpp' file and the 'src/tempTrender.cpp' files
are compiled automatically with just starting root.
(Make sure to include the local path to your include/ directory in the 'rootlogon.C' file for it to work!)
In order to use the implemented functions, you can either run the 'project()' function directly:

    root
    project()

Or create a tempTrender object and call the specific member functions you are interested in with the desired inputs:

    root
    tempTrender* test_2 = new tempTrender("../datasets/smhi-opendata_1_162870_20210926_101011_Lulea.csv")
    test_2->tempOnDay(1,2)

##State of the project:
Currently 1/3 plots have been implemented.

##General stuff #TODO:
* Adress the "Can you predict the probability..." question on page 4 of the pdf. 




