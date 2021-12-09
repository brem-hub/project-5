#pragma once


#define HELP_MESSAGE    "HSE UNIVERSITY, 2021-2022, Kulikov Bogdan, fifth project program.\n"               \
                        "Task: 17\n"                                                                        \
                        "\n"                                                                                \
                        "Usage: program [OPTIONS]...\n"                                                     \
                        "\n"                                                                                \
                        "OPTIONS:\n"                                                                        \
                        " -n, --number-of-bees\t Specify number of bees in the beehive\n"                   \
                        " -h, --help\t\t Get this help message\n"                                           \
                        "\n"                                                                                \
                        "\n"                                                                                \
                        "EXAMPLE:\n"                                                                        \
                        "\t\t* `./program -n 3`\n\n"                                                        \
                        "CORRECT INTERRUPTION:\n"                                                           \
                        "In order to interrupt program correctly and wait for all thread to stop\n"         \
                        "kernel signals are used. Sending SIGINT interruption will cause program to stop.\n"\
                        "\t\t* In Unix systems SIGINT is sent by Ctrl + C hotkey\n\n"                       \
                        "Another way to send SIGINT signal is to use `kill` command from another terminal\n"\
                        "\t\t* `kill -SIGINT process_pid`\n\n"                                              \
                        "ADDITIONAL INFORMATION:\n"                                                         \
                        "Debugging from CLion can be difficult due to internal bug in Clion\n"              \
                        "\tCLion local terminal does not allow to send SIGINT with `Ctrl + C`.\n\n"         \
                        "`stop_program.sh` script is provided to stop the program correctly.\n"             \
                        "\tIt stops the program from bin/ folder only,\n"                                   \
                        "\tso build and launch program from bin/"


#define ARGC_EXCEPTION_MESSAGE  "Incorrect program input\n" \
                                "Try 'program --help(-h)' for more information."


