#pragma once

#include "List3.h"

/*
	List3<int> p;
	p.push(5);
	p.push(3);
	p.push(56);
	p.push(37);
	p.push(1);

	sortMerge<int>(&p);
	p.trace();
*/

template<typename T>
bool __sortMerge(List3<T> *str)
{
    List3 <T> A, B;
    bool writeA = true;

    A.push((*str)[0]);
    for (int i = 1; i < str->length(); i ++)
    {
        if ((*str)[i] < (*str)[i-1])
            writeA = !writeA;

        if (writeA) A.push((*str)[i]);
            else B.push((*str)[i]);
    }

    if (B.length() == 0) return true;

    str->clear();

    int ib = min(1, A.length())-1, ia = min(1, B.length())-1;
    while (ib != -1 || ia != -1)
    {
        if (ib == -1)
        {
            str->push(A[ia]);
            ia = (ia < (int)A.length()-1)?ia+1:-1;
        } else
        if (ia == -1)
        {
            str->push(B[ib]);
            ib = (ib < (int)B.length()-1)?ib+1:-1;
        } else
        {
            if (A[ia] <= B[ib])
            {
                str->push(A[ia]);
                ia = (ia < (int)A.length()-1)?ia+1:-1;
            } else
            {
                str->push(B[ib]);
                ib = (ib < (int)B.length()-1)?ib+1:-1;
            }
        }
    }
    return false;
}

template<typename T>
void sortMerge(List3<T> *str)
{
	while (!__sortMerge<T>(str));
}