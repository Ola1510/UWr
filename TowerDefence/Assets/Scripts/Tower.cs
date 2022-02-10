using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tower : MonoBehaviour
{
    [SerializeField]
    Transform target;

    [SerializeField]
    private int rotation_speed;

    [SerializeField]
    private GameObject bullet;

    [SerializeField]
    private float force;

    [SerializeField]
    private float cool_down; //odstep mniedzy strzalami

    private float time;

    [SerializeField]
    private Transform bullet_spawn_point;

    private List<Enemy> enemies_in_range = new List<Enemy>();

    [SerializeField]
    private AudioSource shot_audio;

    [SerializeField]
    private AudioClip audio_clip;

    void Start()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        var comp_enemy = other.gameObject.GetComponent<Enemy>();
        if (comp_enemy != null) 
        {
            if (target == null) //sprawdzamy czy to co wykrylismy to wrog
            {
                target = other.transform;
            }
            else
            {
                enemies_in_range.Add(comp_enemy);
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        var comp_enemy = other.gameObject.GetComponent<Enemy>();
        if (comp_enemy != null)
        {
            if (other.transform == target)
            {
                target = null;
                if(enemies_in_range.Count > 0)
                {
                    target = enemies_in_range[0].transform;
                }
            }
            enemies_in_range.Remove(comp_enemy);

        }
    }

    void Update()
    {
        if(target == null)
        {
            return;
        }
        var rotation = Quaternion.LookRotation(target.position - transform.position, Vector3.up); //target.position - transform.position --> wektor od nad do przeciwnika
        transform.rotation = Quaternion.RotateTowards(transform.rotation, rotation, rotation_speed*Time.deltaTime);
    
        time += Time.deltaTime;
        if(time > cool_down) //mozemy strzelac
        {
            time = 0;
            var rb = Instantiate(bullet, bullet_spawn_point.position, bullet_spawn_point.rotation).GetComponent<Rigidbody>();
            rb.AddRelativeForce(Vector3.up*force, ForceMode.Impulse);
            Destroy(rb.gameObject, 3); //po 3 sekundach kula znika
            shot_audio.PlayOneShot(audio_clip);
        }
    }
}
