
#ifndef POINT_H
#define POINT_H


/**
  * class Point
  * 
  */

class Point
{
private:
    int number;
    int x;
    int y;
    int demand;

public:

    /**
     * Empty Constructor
     */
    Point ( );

    /**
     * Empty Destructor
     */
    ~Point ( );


    /**
     * Set the value of number
     * @param new_var the new value of number
     */
    void setNumber ( int new_var )     {
            number = new_var;
    }

    /**
     * Get the value of number
     * @return the value of number
     */
    int getNumber ( )     {
        return number;
    }

    /**
     * Set the value of x
     * @param new_var the new value of x
     */
    void setX ( int new_var )     {
            x = new_var;
    }

    /**
     * Get the value of x
     * @return the value of x
     */
    int getX ( )     {
        return x;
    }

    /**
     * Set the value of y
     * @param new_var the new value of y
     */
    void setY ( int new_var )     {
            y = new_var;
    }

    /**
     * Get the value of y
     * @return the value of y
     */
    int getY ( )     {
        return y;
    }

    /**
     * Set the value of demand
     * @param new_var the new value of demand
     */
    void setDemand ( int new_var )     {
            demand = new_var;
    }

    /**
     * Get the value of demand
     * @return the value of demand
     */
    int getDemand ( )     {
        return demand;
    }

};

#endif // POINT_H
