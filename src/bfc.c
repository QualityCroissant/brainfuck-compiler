/* BFC -- A simple Brainfuck compiler
 * Copyright (C) 2024 Finn Chipp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdbool.h>

#define NO_NON_MATCHED_TOKENS 6 /* Number of tokens that don't require matching */
#define STARTING_BLOCK_LEVEL 0 /* The number to start the generated blocks at */

struct non_matched_token {
	char from;
	char *to;
} NON_MATCHED_TOKENS[NO_NON_MATCHED_TOKENS] = { // All the tokens that don't require matching, and what they're to be translated into:
	{'+', "increment"},
	{'-', "decrement"},
	{'>', "increment_pointer"},
	{'<', "decrement_pointer"},
	{'.', "output"},
	{',', "input"}
};

FILE *input_file,
	 *output_file;

void error(char *message, size_t block) { // Function for reporting errors during compilation
    static bool firstTime = true;

    if(firstTime) {
        printf("[BFC] Note: 'Blocks' are things grouped by '[' and ']'. The first block is block 0:\n");
        firstTime = false;
    }
    
    printf("[BFC] Error (Block %zu): %s\n", block, message);
}

char process() { // Function that inputs the characters from the source file one-by-one, and uses them to generate the assembly-output
	static size_t maxBlockLevel = STARTING_BLOCK_LEVEL; // The number new blocks are to be designated (counts up every time a new block is made, so that every block is given a unique number)
	size_t blockLevel; // The number given to the current block
	char next; // The char inputted from the input_file stream last

	while((next = fgetc(input_file)) != EOF) { // For each character in the file:
		if(next == '[') { // If it's a '['
			fprintf(output_file, "\tstart_block %zu\n", blockLevel = maxBlockLevel++); // Start a block, setting the current block to the max block level, and then incrementing the max block level for the content inside this block

			if(process() != ']') // Recurse the inside of the block
			    error("Unmatched block-start '['.", blockLevel); // If it gets to the end of the file before finding a matching ']', the '[' was unmatched
			else
			    fprintf(output_file, "\tend_block %zu\n", blockLevel); // Write the end of the block in the event that it was matched successfully
		} else if(next == ']') { // If it's a ']'
		    return next;
		} else { // If it's a token that doesn't need matching:
			for(size_t i = 0; i < NO_NON_MATCHED_TOKENS; i++) { // Find what it is
				if(NON_MATCHED_TOKENS[i].from == next) { // And write the corresponding assembly-code:
					fprintf(output_file, "\t%s\n", NON_MATCHED_TOKENS[i].to);
					break;
				}
			}
		}
	}

	return 0;
}

int main(int argc, char **argv) {
    if(argc != 3) {
        error("Got wrong amount of commandline arguments; expected 3.", 0);
        return 1;
    }

    // Set input file to first argument passed to script and output file to second argument passed to script:

	input_file = fopen(argv[1], "r"),
	output_file = fopen(argv[2], "a");

    // Run the compilation:

	if(process() != 0)
        error("Unmatched block-end ']'.", 0); // If it does not return 0, this means that the last character returned was a ']', which would've been matched otherwise

    // Tidy-up:

    fclose(input_file);
    fclose(output_file);
	
	return 0;
}
