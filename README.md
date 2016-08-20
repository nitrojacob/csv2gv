csv2gv :- CSV Tree description format to GraphViz .gv format converter

The tool takes in a .csv file, which describes a tree and converts it into a GraphViz .gv format, that can then be graphically plotted using the graphViz tool.
The graphViz tool is a very powerful tool to create Graphs. But the extra learning needed to write a .gv file just to plot a simple tree may not be justifiable.
One can now describe the tree in common spreadsheet applications in an intuitive fashion, export it as a csv; and then use this program to convert it into .gv.
The user's workflow looks something like this:

Tree idea > Spreadsheet Application > .csv > csv2gv > .gv > GraphViz > .png/.jpg

This directory contains and example of such a tree description in sampleTree.csv. Open it in your favourite spreadsheet application, and then play with it.


Pre-requesites
--------------
Needs Graphviz package.
Get it using apt-get install graphviz in Linux
Get it from http://www.graphviz.org/Download..php for other OS.

How it works.
-------------
Expects a sampleTree.csv from the invoking directory. The file name is currently hardcoded in the program.
Creates output.gv on the same directory. This also is hardcoded in the program.

How to generate a picture showing the graph (Linux)
---------------------------------------------------
cd csv2gv;
./bin/Debug/csv2gv;
dot -Tpng output.gv > output.png;

