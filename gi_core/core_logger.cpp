/*********************************************************************************************************************
 * This file is part of 'yet Another Gamma Index Tool'.
 *
 * 'yet Another Gamma Index Tool' is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * 'yet Another Gamma Index Tool' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 'yet Another Gamma Index Tool'; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *********************************************************************************************************************/
 
#include "core_logger.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const string FILENAME = "log.txt";

string createCoreTimestamp()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	string str(buffer);

	return str;
}

void enableCoreLogging()
{
	CORE_LOGGER_ON = true;
}

void disableCoreLogging()
{
	CORE_LOGGER_ON = false;
}

void initializeCoreLogger(bool clearLogs)
{
	ofstream logger;

	if (clearLogs == true)
	{
		logger.open(FILENAME.c_str(), ios::out | ios::trunc);
	}
	else
	{
		logger.open(FILENAME.c_str(), ios::out | ios::app);
	}

	logger << "GAMMA INDEX LOG" << endl;
	logger.close();
	enableCoreLogging();
}

void initializeCoreLogger()
{
	initializeCoreLogger(false);
}

void logCoreMessage(string message)
{
	if (CORE_LOGGER_ON)
	{
		ofstream logger;
		logger.open(FILENAME.c_str(), ios::out | ios::app);
		string entry;
		entry += createCoreTimestamp();
		entry += " : ";
		entry += message;
		logger << entry << endl;
		logger.close();
	}
}

string toString(double value)
{
    ostringstream oss;
    oss << value;
    return oss.str();
}

string planeToString(int value)
{
    if (value < 0 || value > 2)
        return "";

    string planes[3] = {"XY", "XZ", "YZ"};
    return planes[value];
}

string algorithmToString(int value)
{
    if (value < 0 || value > 2)
        return "";

    string algorithms[3] = {"ClassicSolver", "SpiralSolverRectangle", "SpiralSolverWithoutRectangle"};
    return algorithms[value];
}
