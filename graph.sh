#!/bin/bash

make

> files/output/data.txt

for txt_file in files/input/*.txt; do
    echo "${txt_file##*/}"
    bin/main "-i" "${txt_file##*/}" "-o" "null.txt" "-s" "heap"
done

echo > gnuplot.txt

echo "set grid" >> gnuplot.txt

echo "set yrange[0:0.3]" >> gnuplot.txt

echo "set xlabel \"Lines\"" >> gnuplot.txt
echo "set ylabel \"Time\"" >> gnuplot.txt
echo "set title \"Sorting time per lines\"" >> gnuplot.txt

echo "plot \"files/output/data.txt\" smooth zsort with lines" >> gnuplot.txt

echo "pause -1" >> gnuplot.txt

gnuplot "gnuplot.txt"
