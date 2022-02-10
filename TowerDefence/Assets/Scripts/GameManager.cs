using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{

    [SerializeField]
    private int start_cash;

    bool end = false;

    [SerializeField]
    private GameObject Vicotry_canvas;

    [SerializeField]
    private GameObject Lost_canvas;

    public static bool game_reloading = false;

    [SerializeField]
    private TextMeshProUGUI cash_text;

    [SerializeField]
    private TextMeshProUGUI castle_life_text;


    public void Victory()
    {
        if (!end)
        {
            Debug.Log("wygrana!!!");
            Vicotry_canvas.SetActive(true);
        }
        end = true;
    }

    public void Reload_game()
    {
        game_reloading = true;
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void Lost()
    {
        if (!end)
        {
            Debug.Log("przegrana!!!");
            Lost_canvas.SetActive(true);
        }
        end = true;
    }


    // Start is called before the first frame update
    void Start()
    {
        game_reloading = false;
        CashManager.Change_cash(start_cash);
        castle_life_text.text = "Life: " + '6';
    }

    void Update_cash_canvas(int cash)
    {
        cash_text.text = "Cash: " + cash;
    }

    private void OnEnable()
    {
        CashManager.Cash_changed += Update_cash_canvas;
    }

    private void OnDisable()
    {
        CashManager.Cash_changed -= Update_cash_canvas;
    }

    public void Castle_life_change(int castle_life)
    {
        castle_life_text.text = "Life: " + castle_life;
    }

}
