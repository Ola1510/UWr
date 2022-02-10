using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;



public class Castle : MonoBehaviour
{
    
    public int enemyMax;

    private int enemyCount = 0;

    [SerializeField]
    GameManager gameManager;

    [SerializeField]
    private TextMeshProUGUI castle_life_text;

    private void OnTriggerEnter(Collider other) //unity wywola ja kiedy inny obiekt wejdzie w treigger
    {
        var enemy = other.gameObject.GetComponent<Enemy>();
        if (enemy != null)
        {
            enemyCount++;
            if (enemyCount == enemyMax)
            {
                gameManager.Lost();
            }
            Destroy(other.gameObject);
            gameManager.Castle_life_change(enemyMax - enemyCount);
        }
    }

}
