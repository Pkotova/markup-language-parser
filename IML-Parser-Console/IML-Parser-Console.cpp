#include <iostream>
#include "IMLManagementView.h"
/*
* @IML-PARSER 
* @author Petya Kotova
*/
/* @IML Summed up*/
/*

	The language contains 11 tags, and for each of them there is a corresponding 
	closing. Some of the tags have additional attributes that indicate additional 
	information about the operation to be performed.

	The user enters two file names. The first name is for the input 
	file and the second for the output file, and the program must interpret 
	the contents of the input file and write the result to the output. If the input 
	file also contains tags that are not part of the language, display an error message.
	It is necessary to check the correctness of the input.

	Ivan wants to allow correct nesting (or nesting) of tags. If the input is incorrect, 
	the program should display an error message on the standard error output. Ivan's idea is to be 
	able to perform Aggregate, Map and Sorting operations on a list of comparable data (positive and negative 
	fractional numbers). The transformed value can be either a list or a single value (for example, the result of an 
	aggregation operation). IML has three categories of tags:

*/

int main()
{
	IMLManagementView im;
	im.run();
}


/*@ More explanations*/
	/*@ Different tag:*/
		/*		-	Map: <MAP-INC "N"> и <MAP-MLT "N"> where N е floating
					@<MAP-INC "1">1 2 3</MAP-INC> ⇒ 2 3 4
					@<MAP-MLT "2">1 2 3</MAP-MLT> ⇒ 2 4 6

			- Aggregate: <AGG-SUM>, <AGG-PRO>, <AGG-AVG>, <AGG-FST>, <AGG-LST>
					@<AGG-SUM>1 2 3</AGG-SUM> ⇒ 6
					@<AGG-PRO>1 2 3</AGG-PRO> ⇒ 6
					@<AGG-AVG>1 2 3</AGG-AVG> ⇒ 2
					@<AGG-FST>1 2 3</AGG-FST> ⇒ 1
					@<AGG-LST>1 2 3</AGG-LST> ⇒ 3

			- Sorting: <SRT-REV>, <SRT-ORD "ARG">, where ARG is ASC or DSC, <SRT-SLC "N">, N is postive number, <SRT-DST>
				@<SRT-REV>1 2 3</SRT-REV> ⇒ 3 2 1 (обръща списъка)
				@<SRT-ORD "ASC">3 2 1</SRT-ORD> ⇒ 1 2 3 (сортира във възходящ ред (при аргумент “ASC”) или в низходящ ред (при аргумент “DSC”)
				@<SRT-SLC "1">3 2 1</SRT-SLC> ⇒ 2 1 (връща подсписък от посочения индекс нататък)
				@<SRT-DST>4 8 4 3</SRT-DST> ⇒ 4 8 3 (премахва дубликати)
	*/
	/*@ Exception which trigger the application*/
		/*
		100: Missing openning tag
		102: Missing closing tag
		103: Unknown tag used
		101: Missing "<"
		104: Missing ">"
		105: Missing ""
		106: Missing "/"
		107: Missing "-"
		108: Missing parameters
		109: Too much parameters
		110: Unknown parameter types used
		111: Illogical data used between tags
		112: Non-numeric data used
		113: Nesting error
		120: Missing or too much attributes
		130: File doesnt exist
		140: File is empty
		150: Unsupported file
	*/
	/*@Project architecture*/
		/*
		#Data layer:
			- input txt files, output txt files
		#Persistence layer:
			- IMLRepository,ExceptionRepository,ResultRepository
		#Domain Module layer
			- Verification,Reckoning,Tag (root of is-a relationship, used polymorphism)
		#Application layer
			- Parser
		#Presentation layer 
			-IMLManagementView
	*/
	/*@Available filesystem*/
		/*
		* zad1.txt
		* zad2.txt
		* zad3.txt
		* zad4.txt
		*/
	/*@Program flow*/
		/*
		* 1 STAGE: IMLRepository 
		* 2.STAGE: ExceptionRepository
		* 3.STAGE: Parser
		* 4.STAGE: ResultRepository
		* 5.STAGE: IMLManagementView
		*/
	