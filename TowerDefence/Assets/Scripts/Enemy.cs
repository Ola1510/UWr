using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public PathNode next;

    [SerializeField]
    private float eps; // zmienna ktora mowi nam jak blisko punktu muimy byc zeby uznac ze juz dotarlismy do celu

    [SerializeField]
    private float speed; // w [m/s]

    [SerializeField]
    private float rotationSpeed; //w [rad/s]

    [SerializeField]
    private int max_life;

    private int current_life;

    public event System.Action Died;

    [SerializeField]
    private int price;



    // Start is called before the first frame update
    void Awake()
    {
        current_life = max_life;
    }

    // Update is called once per frame
    void Update()
    {
        if (next == null)
            return;
        transform.position += transform.forward * speed * Time.deltaTime;
        Vector3 direction = next.transform.position - transform.position;
        float rotation = rotationSpeed * Time.deltaTime;
        Vector3 newDirection = Vector3.RotateTowards(transform.forward, direction, rotation, 0);
        transform.rotation = Quaternion.LookRotation(newDirection);

        if(Vector3.Distance(transform.position, next.transform.position) < eps)
        {
            next = next.Next();
        }
    }

    private void OnDestroy()
    {
        if(!GameManager.game_reloading)
        {
            Died?.Invoke();
        }
    }

    public void Deal_damage()
    {
        current_life--;
        if(current_life <= 0)
        {
            CashManager.Change_cash(price);
            if(gameObject!=null)
                Destroy(gameObject);
        }
    }
}
