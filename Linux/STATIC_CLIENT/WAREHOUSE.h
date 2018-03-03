
/* 
 * File:   WAREHOUSE.h
* Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "OSTM.h"
/*!
 * WAREHOUSE inherit from OSTM library
 */
class WAREHOUSE : public OSTM {
public:
    /*!
     * Constructor
     */
    WAREHOUSE():OSTM(){
        
    };
    /*!
     * Custom Constructor
     */
    WAREHOUSE(int _version, int _unique_id) : OSTM(_version, _unique_id){
        
    };
    /*!
     * Copy constructor
     */
    WAREHOUSE(const WAREHOUSE& orig);
    /*!
     * de-constructor
     */
    virtual ~WAREHOUSE();
    
    /*
     * WAREHOUSE BASE METHODS
     */
    
    virtual void SetNumber_of_alcatel(int _number_of_alcatel){};
    virtual int GetNumber_of_alcatel(){};
    virtual void SetNumber_of_nokia(int _number_of_nokia){};
    virtual int GetNumber_of_nokia(){};
    virtual void SetNumber_of_huawei(int _number_of_huawei){};
    virtual int GetNumber_of_huawei(){};
    virtual void SetNumber_of_sony(int _number_of_sony){};
    virtual int GetNumber_of_sony(){};
    virtual void SetNumber_of_samsung(int _number_of_samsung){};
    virtual int GetNumber_of_samsung(){};
    virtual void SetNumber_of_iphones(int _number_of_iphones){};
    virtual int GetNumber_of_iphones(){};
    virtual void SetShop_name(std::string _shop_name){};
    virtual std::string GetShop_name(){};
    virtual void SetShop_address(std::string _shop_address){};
    virtual std::string GetShop_address(){};
    
private:

};

#endif /* WAREHOUSE_H */

