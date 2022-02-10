using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class CashManager
{
    static int cash;

    public static event Action<int> Cash_changed;

    public static void Change_cash(int delta)
    {
        cash += delta;
        Cash_changed?.Invoke(cash);
    }

}
