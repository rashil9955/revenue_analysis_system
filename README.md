# Event Center Revenue Analysis System

## Overview
This program processes and analyzes holiday event data for a local event center, generating detailed financial reports from attendance and pricing information. It reads event data from a text file and produces comprehensive analysis including attendance figures, per-person costs, and revenue calculations.

## Features
- Reads event data from an input file (dec_events.txt)
- Processes multiple event records including date, attendance, and cost per person
- Calculates gross revenue for each event
- Generates a formatted report with key metrics
- Computes summary statistics including:
  - Total attendance across all events
  - Total revenue generated
  - Average cost per attendee

## File Structure
- `events_rash.c`: Main program file
- `dec_events.txt`: Input file containing event data
- `report.txt`: Output file containing the generated report

## Input File Format
The input file should contain space-separated values in the following format:
```
day attendance cost
```
Example:
```
1 450 24.99
2 120 15.00
```

## Functions
- `readEventData`: Reads a single line of event data from the input file
- `calculateRevenue`: Computes revenue for an event based on attendance and cost
- `printReportLine`: Formats and prints a single line of the report
- `printSummary`: Generates summary statistics for all events

## Usage
1. Ensure `dec_events.txt` is present in the specified directory
2. Compile the program using a C compiler
3. Run the executable
4. Check `report.txt` for the generated report

## Technical Requirements
- C compiler (Standard C)
- File I/O capabilities
- Text file read/write permissions in the working directory

## Author
Rashil Shibakoti  
CSC150 Fall 2023  
South Dakota State University

## Notes
- The program can handle varying numbers of event records
- All monetary values are processed with 2 decimal places
- Input file must follow the specified format for proper execution
