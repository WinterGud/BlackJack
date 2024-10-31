#include "Logger.h"

Logger::Logger(const std::string& fileName)
{
    m_logFile.open(fileName, std::ios::app); 
    if (!m_logFile.is_open()) {
        std::cerr << "Error opening log file." << '\n'; 
    } 
}

Logger& Logger::getInstance(const std::string fileName)
{
    static Logger m_logger(fileName);
    
    return m_logger;
}

Logger::~Logger()
{
    m_logFile.close();
}

void Logger::log(LogLevel level, const std::string& logText)
{
    time_t now = time(0); 
    tm* timeinfo = localtime(&now); 
    char timestamp[20]; 
    strftime(timestamp, sizeof(timestamp), 
             "%Y-%m-%d %H:%M:%S", timeinfo); 
    
    std::ostringstream logEntry; 
    logEntry << "[" << timestamp << "] "
             << levelToString(level) << ": " << logText 
             << '\n'; 
    
    std::cout << logEntry.str(); 
    
    if (m_logFile.is_open())
    { 
        m_logFile << logEntry.str(); 
        m_logFile.flush();
    } 
}

std::string Logger::levelToString(LogLevel level)
{ 
    switch (level) { 
    case DEBUG: 
        return "DEBUG"; 
    case INFO: 
        return "INFO"; 
    case WARNING: 
        return "WARNING"; 
    case ERROR: 
        return "ERROR"; 
    case CRITICAL: 
        return "CRITICAL"; 
    default: 
        return "UNKNOWN"; 
    } 
} 
