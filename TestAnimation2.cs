//Animator

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Elevator : MonoBehaviour
{
    public Animator animator;
        
    void Start()
    {
        animator = GetComponent<Animator>();
    }
        
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.UpArrow))
        {
            animator.Play("anim1");

        }
        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            animator.Play("anim2");
        }

        if (animator.GetCurrentAnimatorStateInfo(0).IsName("anim1") &&
            animator.GetCurrentAnimatorStateInfo(0).normalizedTime >= 1f)
        {
            print(""+ animator.name);
            animator.Play("anim2");
        }
/*        if (animator.GetCurrentAnimatorStateInfo(0).IsName("anim2") &&
            animator.GetCurrentAnimatorStateInfo(0).normalizedTime >= 1f)
        {
            print("" + animator.name);
            animator.Play("anim1");
        }
*/
    }
}
