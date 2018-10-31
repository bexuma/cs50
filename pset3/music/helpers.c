// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

#define FLAT 98
#define SHARP 35

int to_x(int);
int to_y(int);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = atoi(&fraction[0]);
    int y = atoi(&fraction[2]);

    return (8 / y) * x;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int semitone, octave;

    if (strlen(note) == 2)
    {
        semitone = (int) note[0];
        octave = atoi(&note[1]);
    }
    // accidental sign is present, e.g. A#6
    else
    {
        semitone = (int) note[0] + (int) note[1];
        octave = atoi(&note[2]);
    }

    int n = to_x(semitone) + 12 * to_y(octave);

    double hertz = pow(2.00, n / 12.0) * 440;
    return round(hertz);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") || strlen(s) == 6 || strlen(s) == 7)
    {
        return false;
    }

    return true;
}

int to_x(int ascii)
{
    switch (ascii)
    {
        // C
        case 67:
            return -9;
            break;
        // C#
        case 67+SHARP:
            return -8;
            break;
        // Db
        case 68+FLAT:
            return -8;
            break;
        // D
        case 68:
            return -7;
            break;
        // D#
        case 68+SHARP:
            return -6;
            break;
        // Eb
        case 69+FLAT:
            return -6;
            break;
        // E
        case 69:
            return -5;
            break;
        // F
        case 70:
            return -4;
            break;
        // F#
        case 70+SHARP:
            return -3;
            break;
        // Gb
        case 71+FLAT:
            return -3;
            break;
        // G
        case 71:
            return -2;
            break;
        // G#
        case 71+SHARP:
            return -1;
            break;
        // Ab
        case 65+FLAT:
            return -1;
            break;
        // A
        case 65:
            return 0;
            break;
        // A#
        case 65+SHARP:
            return 1;
            break;
        // Bb
        case 66+FLAT:
            return 1;
            break;
        // B
        case 66:
            return 2;
            break;

        default:
            return 212;
    }
}

int to_y(int octave)
{
    switch (octave)
    {
        case 4:
            return 0;
            break;
        case 5:
            return 1;
            break;
        case 6:
            return 2;
            break;
        case 7:
            return 3;
            break;
        case 8:
            return 4;
            break;
        case 0:
            return -4;
            break;
        case 1:
            return -3;
            break;
        case 2:
            return -2;
            break;
        case 3:
            return -1;
            break;
        default:
            return 213;
    }
}