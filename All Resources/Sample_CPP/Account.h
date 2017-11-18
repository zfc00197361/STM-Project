/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Account.h
 * Author: zoltan
 *
 * Created on November 17, 2017, 6:13 PM
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Tobj.h"

class Account : public Tobj<T> {
public:
    Account(double value, int accountNumber, string accountHolder) : Tobj<T>(this){};
    virtual ~Account();
    void remove(double value);
    void add(double value);
    void setAccountHolder(string accountHolder);
    string getAccountHolder() const;
    void setAccountNumber(int accountNumber);
    int getAccountNumber() const;
    void setAmount(double amount);
    double getAmount() const;
    int getVersion();
    void increase();
private:
    double amount;
    int accountNumber;
    string accountHolder;
    

};

#endif /* ACCOUNT_H */

