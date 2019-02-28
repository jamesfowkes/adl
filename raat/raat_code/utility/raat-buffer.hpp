#ifndef _RAAT_BUFFER_H_
#define _RAAT_BUFFER_H_

class RAATBuffer
{
    public:
        RAATBuffer(char * buffer, uint16_t length);
        ~RAATBuffer();
        bool writeChar(char c);
        bool writeString(const char * s);
        bool writeLine(const char * s);
    
        #if defined(PROGMEM)
        bool writeStringP(const char * s);
        bool writeLineP(const char * s);
        #endif
        
        void remove(uint32_t chars);
                
        void reset(void);
        char * c_str(void);
        
        bool isFull(void);
        void attach(char * buffer, uint16_t length);
        void detach(void);
        uint16_t length(void);
	
	int strncmp(char * needle, int n);
    private:
        char * m_buffer;
        uint16_t m_maxLength;
        uint16_t m_writeIndex;
};

#endif
