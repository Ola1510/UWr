using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaveSpawner : MonoBehaviour
{
    [SerializeField]
    private List <GameObject> enemies;

    [System.Serializable]
    public struct wave
    {
        public int enemy_1count;
        public int enemy_2count;   
        public int enemy_3count;
    }

    [SerializeField]
    private List<wave> waves;

    private List<GameObject> current_enemies = new List<GameObject>();

    [SerializeField]
    private float time;

    [SerializeField]
    private PathNode first_node;

    private int created_enemies;
    private int killed_enemies;

    bool all_wave = false;

    int wave_number;

    [SerializeField]
    GameManager gameManager;

    IEnumerator spawn_wave(int idx)
    {
        wave w = waves[idx];
        int all_enemies = w.enemy_1count + w.enemy_2count + w.enemy_3count;
        all_wave = false;
        while(all_enemies > 0)
        {
            yield return new WaitForSeconds(time); //yield break --> return dla zwyklej metody 
            bool success = false;
            Enemy enemy = null;
            while(!success)
            {
                int enemy_number = UnityEngine.Random.Range(1, 4);
                switch (enemy_number)
                {
                    case 1:
                        if (w.enemy_1count > 0)
                        {
                            w.enemy_1count--;
                            enemy = Instantiate(enemies[0], transform.position, Quaternion.identity).GetComponent<Enemy>(); //tworzy gameobject z tablicy enemies[], w okreslonym miejscu
                            success = true;
                        }
                        break;
                    case 2:
                        if (w.enemy_2count > 0)
                        {
                            w.enemy_2count--;
                            enemy = Instantiate(enemies[1], transform.position, Quaternion.identity).GetComponent<Enemy>();  //tworzy gameobject z tablicy enemies[], w okreslonym miejscu
                            success = true;
                        }
                        break;
                    case 3:
                        if (w.enemy_3count > 0)
                        {
                            w.enemy_3count--;
                            enemy = Instantiate(enemies[2], transform.position, Quaternion.identity).GetComponent<Enemy>();  //tworzy gameobject z tablicy enemies[], w okreslonym miejscu
                            success = true;
                        }
                        break;
                }
            }
            all_enemies--;
            created_enemies++;
            enemy.next = first_node;
            enemy.Died += Enemy_died_handler; // += tak przypisujemy cos do eventu  
        }
        all_wave = true;
    }

    void Enemy_died_handler()
    {
        killed_enemies++;
        if(killed_enemies == created_enemies && all_wave)
        {
            if (wave_number+1 < waves.Count)
            {
                wave_number++;
                StartCoroutine(spawn_wave(wave_number));
            }
            else
            {
                gameManager.Victory();
            }
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(spawn_wave(0)); 
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
