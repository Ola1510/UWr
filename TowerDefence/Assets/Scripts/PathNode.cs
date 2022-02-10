using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PathNode : MonoBehaviour
{
    [SerializeField]
    private PathNode next; // wskazuje na kolejny element sxiezki

    void OnDrawGizmos() //rysujemy obiekty, kotre sa widoczne tylko w widoku sceny ale nie gry
    {
        Gizmos.DrawWireSphere(transform.position, 0.3f);
        if(next != null)
            Gizmos.DrawLine(transform.position, next.transform.position);
    }

    public PathNode Next()
    {
        return next;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
