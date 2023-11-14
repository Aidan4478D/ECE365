## DSA II Program #1 - Spellcheck

For this assignment, a hash table class was created and a program uses the hash table to load a "dictionary" and spell check a "document".

To view the full details for this assignment, please refer to the link below. 
https://view.officeapps.live.com/op/view.aspx?src=http%3A%2F%2Ffaculty.cooper.edu%2Fsable2%2Fcourses%2Ffall2023%2Fece365%2Fhash%2Fece365_spellCheck.docx&wdOrigin=BROWSELINK

Grade and Comments: 

Grade: 96

Comments:

The final submission works perfectly for five of my six test cases. For my final test case (the second test case with my largest dictionary, involving a large spell check file also), there is a single mistake in the output! There is one unknown word being incorrectly reported as a long word. It happens to have exactly 20 characters. FYI, the word is "hierarchical-faceted"! It looks like you have an off-by-one error when you check for long words in the code; 20 is allowed, 21 is not. (I thought there were other cases of this, but maybe not!) -4 point
