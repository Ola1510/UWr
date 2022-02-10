using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    private void OnCollisionEnter(Collision collision)
    {
        var enemy = collision.gameObject.GetComponent<Enemy>();
        if ( enemy != null)
        {
            enemy.Deal_damage(); //sprawdzamy czy przeciwnki umarl
            Destroy(gameObject); //niszczymy kule
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
