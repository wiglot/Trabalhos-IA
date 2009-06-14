
#ifndef READ_H
#define READ_H
#include <sstream>

class InstanceVRP;

class Read {

private:
    string file;
    
public:
    /**
     * Empty Constructor
     */
    Read ( );

    /**
     * Empty Destructor
     */
    ~Read ( );

    /**
     * @return InstanceVRP
     */
    InstanceVRP readVRP ( );

    /**
     * Set the value of file
     * @param new_var the new value of file
     */
    void setFile ( string new_var )     {
            file = new_var;
    }

    /**
     * Get the value of file
     * @return the value of file
     */
    string getFile ( )     {
        return file;
    }
    
    static int str2int(string str)   {
		int value;
		istringstream stm(str, istringstream::in);
		stm >> value;
		return (value);
	}    
};

#endif // READ_H
