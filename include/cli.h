#ifndef CLI_H
#define CLI_H

/**
 * @brief Parses the command-line arguments provided by the user.
 *
 * This function is responsible for interpreting the arguments passed to the program
 * upon execution. It directs the flow of the program based on the user's input,
 * such as choosing between an interactive session or executing a specific command
 * with provided arguments.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of character pointers to the arguments.
 */
void parse_args(int argc, char *argv[]);

/**
 * @brief Prints the correct usage of the program.
 *
 * This function is called when the user provides incorrect or insufficient
 * command-line arguments. It displays a help message to standard output,
 * outlining the valid commands, options, and argument formats to guide the
 * user on how to properly interact with the application.
 */
void print_usage();

#endif