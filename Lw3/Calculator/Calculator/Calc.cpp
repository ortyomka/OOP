#include "stdafx.h"

#include "Calc.h"

bool CCalc::Var(std::string name)
{
	if (m_variables.find(name) == m_variables.end() && m_functions.find(name) == m_functions.end())
	{
		m_variables[name] = 0;
		return true;
	}
	std::cout << "Variable or function with name \""<< name << "\" have declarated\n";
	return false;
}

std::map<std::string, double> CCalc::GetVariables() const
{
	return m_variables;
}

bool CCalc::Let(std::string firstName, std::string secondName)
{
	if (m_variables.find(firstName) != m_variables.end())
	{
		if (m_variables.find(secondName) != m_variables.end())
		{
			m_variables[firstName] = m_variables[secondName];
			return true;
		}
		std::cout << "Variable with name \"" << secondName << "\" have not declarated\n";
		return false;
	}
	std::cout << "Variable with name \"" << firstName << "\" have not declarated\n";
	return false;
}

bool CCalc::Let(std::string name, double value)
{
	if (m_variables.find(name) != m_variables.end())
	{
		m_variables[name] = value;
		return true;
	}
	std::cout << "Variable with name \"" << name << "\"have not declarated\n";
	return false;
}

bool CCalc::Fn(std::string functionName, std::string name)
{
	if (m_functions.find(functionName) == m_functions.end() && m_variables.find(functionName) == m_variables.end())
	{
		if (m_variables.find(name) != m_variables.end())
		{
			m_functions[functionName] = &m_variables[name];
			return true;
		}
		if (m_functions.find(name) != m_functions.end())
		{
			m_functions[functionName] = m_functions[name];
			return true;
		}
		std::cout << "Function or variables with name \"" << name << "\" have not declarated\n";
	}
	std::cout << "Function or variables with name \"" << functionName << "\" have declarated\n";
	return false;
}

std::map<std::string, double*> CCalc::GetFunctions() const
{
	return m_functions;
}


