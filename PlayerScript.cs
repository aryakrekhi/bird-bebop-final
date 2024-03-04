using UnityEngine;
using Debug = UnityEngine.Debug;

using System.Security.Cryptography;
using System.Collections.Specialized;
using TMPro;
using static UnityEditor.Timeline.TimelinePlaybackControls;

public class PlayerMovement : MonoBehaviour
{
    // Start is called before the first frame update
    public float walkSpeed = 10;
    public float movementX;
    public float jump;

    public bool isJumping;
    private int coincount;

    private Animator anim;
    public CoinManager cm;
    public TextMeshProUGUI coinText;

    Rigidbody2D rb;


    public static PlayerMovement Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
        }
    }


    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        coincount = 0;

    }

    private void Update()
    {

        movementX = Input.GetAxis("Horizontal");
        rb.velocity = new Vector2(walkSpeed * movementX, rb.velocity.y);
        if (Input.GetButtonDown("Jump") && isJumping == false)
        {
            rb.AddForce(new Vector2(rb.velocity.x, jump));
            anim.SetBool("New Bool", true);

        }
        if (rb.velocity.x == 0 && rb.velocity.y == 0)
        {
            anim.SetBool("New Bool", false);
        }
    }



    private void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ground"))
        {
            isJumping = false;
        }

    }

    private void OnCollisionExit2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ground"))
        {
            isJumping = true;
        }

    }

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.CompareTag("Plant"))
        {

            Destroy(other.gameObject);
            cm.coincount++;

            coincount = coincount + 1;
            SetCountText();

        }
    }

    void SetCountText()
    {
        coinText.text = "Plants: " + coincount.ToString();
        if (coincount == 7)
        {
            coinText.text = "You Win!";
        }
    }

    

}