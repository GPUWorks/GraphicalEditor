#ifndef _TYPEWRITER_H
#define _TYPEWRITER_H

#include <string>
#include "Coordinates.h"
#include "MenuOperator.h"

class MenuOp;



class TypeWriter
{
private:
	bool isOn;
	bool hasCompleted;
	string buffer;
	string initialString;
	Coordinates *bottom_left;

	MenuOp *selectedOperation;	

public:
	TypeWriter(float x, float y);
	TypeWriter(float x, float y, string str);

	void start();
	void stop();	
	void setSelectedOperation(MenuOp *s);
	void performSelectedOp();
	MenuOp *getSelectedOperation();

	void addChar(char c);
	void clear();
	void drawString();
	bool isBusy();
	bool isFinished();
	string getBufferedInput();
	void setBufferedContents(string str);
	void setInitialString(string str);
};

TypeWriter::TypeWriter(float x, float y)
{
	isOn = false;
	hasCompleted = false;
	bottom_left = new Coordinates(x, y, 0);
	selectedOperation = NULL;
}

TypeWriter::TypeWriter(float x, float y, string str)
{
	isOn = false;
	hasCompleted = false;
	bottom_left = new Coordinates(x, y, 0);
	buffer = "";
	initialString = str;
	selectedOperation = NULL;
}

void TypeWriter::addChar(char c)
{	
	LOG("c = " << (int)c);
	if(isOn && !hasCompleted)
	{
		if(c == 13)				//Enter Key
		{
			hasCompleted = true;
			return;
		}

		if(c == 127 || c == 8)  //Backspace Key or Delete Key
		{
			LOG("HERE");			
			buffer = buffer.substr(0, buffer.size() - 2);				
		}

		buffer += c;	
		drawString();
	}
}

void TypeWriter::drawString()
{		
	glColor4f(1, 0, 0, 1);
	glRasterPos2f(bottom_left->get(X_AXIS), bottom_left->get(Y_AXIS));

	for(int i=0; i<initialString.length(); i++)			
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, initialString[i]);
		

	for(int i=0; i<buffer.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
}

void TypeWriter::clear()
{	
	buffer = "";
}

void TypeWriter::start()
{
	isOn = true;	
	hasCompleted = false;
}

void TypeWriter::stop()
{
	isOn = false;
	hasCompleted = false;
	buffer = "";
}

void TypeWriter::setSelectedOperation(MenuOp *s)
{
	selectedOperation = s;
}

MenuOp *TypeWriter::getSelectedOperation()
{
	return selectedOperation;
}

bool TypeWriter::isBusy()
{
	return isOn;
}

bool TypeWriter::isFinished()
{
	return hasCompleted;
}

string TypeWriter::getBufferedInput()
{
	return buffer;
}

void TypeWriter::setBufferedContents(string str)
{
	buffer = str;
}
	
void TypeWriter::setInitialString(string str)
{
	initialString = str;
}


#endif