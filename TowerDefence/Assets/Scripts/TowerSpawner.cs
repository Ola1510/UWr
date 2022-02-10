using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TowerSpawner : MonoBehaviour
{

    [SerializeField]
    private Button button;

    [SerializeField]
    int price;

    [SerializeField]
    GameObject new_tower;

    void Cash_handler(int cash)
    {
        if(cash >= price)
        {
            button.interactable = true;
        }
        else
        {
            button.interactable = false;
        }
    }

    public void Tower_create()
    {
        Instantiate(new_tower, transform.position, Quaternion.identity);
        CashManager.Change_cash(-price);
        Destroy(gameObject);
    }

    void OnEnable()
    {
        CashManager.Cash_changed += Cash_handler;
    }

    void OnDisable()
    {
        CashManager.Cash_changed -= Cash_handler;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
