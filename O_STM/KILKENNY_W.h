
/* 
 * File:   KILKENNY_W.h
 * Author: Zoltan Fuzesi
 * IT Carlow : C00197361
 *
 * Created on January 17, 2018, 8:02 PM
 */

#ifndef KILKENNY_W_H
#define KILKENNY_W_H
#include "WAREHOUSE.h"
#include <string>
#include <memory>
#include <iostream>
/*!
 * Inherit from WAREHOUSE
 */
class KILKENNY_W : public WAREHOUSE {
public:
    /*!
     * Constructor
     */
    KILKENNY_W(): WAREHOUSE(){
        
        this->_shop_address = "Kilkenny High Street";
        this->_shop_name = "KILKENNY K_WAREHOUSE";
        this->_number_of_iphones = 200;
        this->_number_of_samsung = 200;
        this->_number_of_sony = 200;
        this->_number_of_huawei = 200;
        this->_number_of_nokia = 200;
        this->_number_of_alcatel = 200;
    };
    /*!
     * Custom constructor
     */
    KILKENNY_W(std::string address, std::string shop_name, int iphone, int samsung, int sony, int huawei, int nokia, int alcatel): WAREHOUSE(){
        /*
         * copy over values
         */
        this->_shop_address = address;
        this->_shop_name = shop_name;
        this->_number_of_iphones = iphone;
        this->_number_of_samsung = samsung;
        this->_number_of_sony = sony;
        this->_number_of_huawei = huawei;
        this->_number_of_nokia = nokia;
        this->_number_of_alcatel = alcatel;
        
    };
    /*!
     * Custom constructor, used by the library for deep copying
     */
    KILKENNY_W(std::shared_ptr<WAREHOUSE> obj, int _version, int _unique_id): WAREHOUSE(_version, _unique_id){
        /*
         * copy over values
         */
        this->_shop_address = obj->GetShop_address();
        this->_shop_name = obj->GetShop_name();
        this->_number_of_iphones = obj->GetNumber_of_iphones();
        this->_number_of_samsung = obj->GetNumber_of_samsung();
        this->_number_of_sony = obj->GetNumber_of_sony();
        this->_number_of_huawei = obj->GetNumber_of_huawei();
        this->_number_of_nokia = obj->GetNumber_of_nokia();
        this->_number_of_alcatel = obj->GetNumber_of_alcatel();
    }
    /*!
     * Copy constructor
     */
    KILKENNY_W(const KILKENNY_W& orig);
    /*!
     * Operator
     */
    KILKENNY_W operator=(const KILKENNY_W& orig){};
    /*!
     * de-constructor
     */
    virtual ~KILKENNY_W();
    /*
     * Implement OSTM virtual methods
     */
    //virtual std::shared_ptr<KILKENNY_W> _cast(std::shared_ptr<OSTM> _object);
    virtual void copy(std::shared_ptr<OSTM> to, std::shared_ptr<OSTM> from);
    virtual std::shared_ptr<OSTM> getBaseCopy(std::shared_ptr<OSTM> object);
    virtual void toString();
    /*
     * Implement Warehouse methods
     */
    virtual void SetNumber_of_alcatel(int _number_of_alcatel);
    virtual int GetNumber_of_alcatel();
    virtual void SetNumber_of_nokia(int _number_of_nokia);
    virtual int GetNumber_of_nokia();
    virtual void SetNumber_of_huawei(int _number_of_huawei);
    virtual int GetNumber_of_huawei();
    virtual void SetNumber_of_sony(int _number_of_sony);
    virtual int GetNumber_of_sony();
    virtual void SetNumber_of_samsung(int _number_of_samsung);
    virtual int GetNumber_of_samsung();
    virtual void SetNumber_of_iphones(int _number_of_iphones);
    virtual int GetNumber_of_iphones();
    virtual void SetShop_name(std::string _shop_name);
    virtual std::string GetShop_name();
    virtual void SetShop_address(std::string _shop_address);
    virtual std::string GetShop_address();
    
    
private:
    std::string _shop_address;
    std::string _shop_name;
    int _number_of_iphones;
    int _number_of_samsung;
    int _number_of_sony;
    int _number_of_huawei;
    int _number_of_nokia;
    int _number_of_alcatel;

};

#endif /* KILKENNY_W_H */

