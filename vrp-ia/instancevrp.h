
#ifndef INSTANCEVRP_H
#define INSTANCEVRP_H

class Point;

class InstanceVRP
{
public:

    /**
     * Empty Constructor
     */
    InstanceVRP ( );

    /**
     * Empty Destructor
     */
    ~InstanceVRP ( );

    /**
     * Set the value of points
     * @param new_var the new value of points
     */
    void setPoints ( vector< Point * > new_var )     {
            points = new_var;
    }

    /**
     * Get the value of points
     * @return the value of points
     */
    vector< Point * > getPoints ( )     {
        return points;
    }

    /**
     * Set the value of deposit
     * @param new_var the new value of deposit
     */
    void setDeposit ( int new_var )     {
            deposit = points.at(new_var);
            points.erase(points.begin() + new_var);
    }

    /**
     * Get the value of deposit
     * @return the value of deposit
     */
    Point* getDeposit ( )     {
        return deposit;
    }

    /**
     * @param  point
     */
    void addPoint (Point *point )
    {
    	points.push_back(point);
    }


    /**
     * @return unsigned int
     */
    unsigned int getNumPoints ( )
    {
    	return points.size();
    }


    /**
     * @return Point*
     * @param  index
     */
    Point* getPoint (unsigned short index )
    {
    	return points.at(index);
    }

	/** 
	 * @brief Seta nome da Instancia
	 * @param name Nome da Instancia.
	 */
	inline void setName(string name){
		this->name = name;
	}
	
	/**
	 * @brief Devolve nome da Instancia.
	 */
	inline string getName(){ return this->name; }

	/**
	 * @brief Indica a capacidade de transporte dos veiculos.
	 * @param c Capacidade de transporte.
	 */
	inline void setCapacity(int c){ this->capacity = c; }
	
	/**
	 * @brief Devolve a capacide de transporte.
	 */
	inline int getCapacity(){return this->capacity;}

private:

    // Private attributes
    //  
    int capacity;
	string name;
    vector< Point* > points;
    Point* deposit;


};

#endif // INSTANCEVRP_H
