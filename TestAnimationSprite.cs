using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestAnimationSprite : MonoBehaviour
{
    public Animator animator;
    public SpriteRenderer sr;

    public string anim_cur = "hero_idle";

    bool isMove = false;
    bool isAttack = false;

    void Start()
    {
        animator.Play("hero_idle");
    }

    void Update()
    {
        Move();
        Attack();
    }

    private void Move()
    {
        if (isAttack == true) return;

        if (Input.GetKey(KeyCode.RightArrow))
        {
            isMove = true;
            sr.flipX = true;
            SetAnimation("hero_walk");
            transform.position += transform.right * 3.0f * Time.deltaTime;
        }
        else if (Input.GetKey(KeyCode.LeftArrow))
        {
            isMove = true;
            sr.flipX = false;
            SetAnimation("hero_walk");
            transform.position -= transform.right * 3.0f * Time.deltaTime;
        }
        else
        {
            isMove = false;
            SetAnimation("hero_idle");
        }
    }

    void Attack()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            isAttack = true;
            SetAnimation("hero_attack");
        }
        if (animator.GetCurrentAnimatorStateInfo(0).IsName("hero_attack") &&
            animator.GetCurrentAnimatorStateInfo(0).normalizedTime >= 1.0f) //에니메이션 종료 
        {
            isAttack = false;  
        }
    }

    void SetAnimation( string anim  )
    {
        if (anim_cur == anim) return;
        anim_cur = anim;

        if (anim == "hero_idle")    { animator.Play(anim); }
        if (anim == "hero_walk")    { animator.Play(anim); }
        if (anim == "hero_attack")  { animator.Play(anim); }
    }

}
