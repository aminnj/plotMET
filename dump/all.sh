rm pdfs/*.pdf
# root -b -q plot.C
root -b -q dump.C
gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=merged.pdf pdfs/*.pdf
web merged.pdf
