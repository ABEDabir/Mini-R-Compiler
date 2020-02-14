cmake_minimum_required(VERSION 3.12)
project(CompilateurR C)

set(CMAKE_C_STANDARD 99)

add_executable(CompilateurR compilateur.c global.h analyseur_lexical.c analyseur_lexical.h errors.c errors.h analyseur_syntaxique.c analyseur_syntaxique.h analyseur_semantique.c analyseur_semantique.h)