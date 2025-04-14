using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestAnimation : MonoBehaviour
{
    public Animation anima;     //편집 //Ctrl+6

    Animator animator;          //Animator, Animator Controller, AnimatorClip //Ctrl+6
    string anim_cur;

    void Start()
    {
        //에니메이션
        //print("" + anima.name);

        //에니메이터 얻어오기
        animator = GetComponent<Animator>();
        //animator.speed = 2.0f;  //스피드변경

        //에니메이션 state
        AnimatorStateInfo state = animator.GetCurrentAnimatorStateInfo(0);
        //state.length
        //state.normalizedTime  //경과시간 0 ~ 1.0f

        //에니메이션 클립 정보 얻어오기
        AnimatorClipInfo[] clips = animator.GetCurrentAnimatorClipInfo(0); //anim.layerCount
        for (int i = 0; i < clips.Length; i++)
        {
            print("clip:" + clips[i].clip.name + " length:" + clips[i].clip.length);
        }


    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            animator.Play("idle");
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            animator.Play("walk");
            //anim.CrossFade("walk", 0.3f);
        }

        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            animator.speed = 1.0f;
            animator.Play("death");
            Invoke("SetAnimationIdle", 1.0f);
        }

        if (animator.GetCurrentAnimatorStateInfo(0).IsName("CurrentStateName") &&
            animator.GetCurrentAnimatorStateInfo(0).normalizedTime >= 1.0f)
        {
            Debug.Log("Current State Name 애니메이션 종료.");
        }

        if (animator.GetCurrentAnimatorStateInfo(0).IsName("CurrentStateName") &&
            animator.GetCurrentAnimatorStateInfo(0).normalizedTime < 1.0f &&
            animator.GetCurrentAnimatorStateInfo(0).normalizedTime >= 0.8f)
        {
            if (Input.GetKeyDown(KeyCode.K))
            {
                Debug.Log("애니메이션 진행도 80% ~ 100% 사이 구간에 키입력.");
            }
        }
    }

    void SetAnimationIdle() { animator.Play("idle"); }

    void SetAnimation(string anim, string next ="")
    {
        if (anim_cur == anim) return;
        anim_cur = anim;
        animator.Play(anim_cur);

        if(next != "") StartCoroutine(SetAnimationNext(next));
    }

    IEnumerator SetAnimationNext(string anim)
    {
        float delay = GetAnimationDuration(anim_cur);
        yield return new WaitForSeconds(delay); // 1초 지연
        SetAnimation(anim);
    }

    float GetAnimationDuration(string anim)
    {
        AnimationClip[] clips = animator.runtimeAnimatorController.animationClips;
        for (int i = 0; i < clips.Length; i++) {
            if (clips[i].name == anim) return clips[i].length;
        }

        return 0;
    }
}

/*
Animator anim;
anim.setTrigger("Attack");
yield return new WaitForEndOfFrame();

//현재 재생 중인 애니메이션 재생시간
float curAnimationTime = anim.GetCurrentAnimatorStateInfo(0).length;
yield return new WaitForSeconds(curAnimationTime);
*/

/*
Animator animator;

void Start()
{
animator = GetComponent<Animator>();
}

void Update()
{
float h = Input.GetAxis("Horizontal");
float v = Input.GetAxis("Vertical");
bool fire = Input.GetButtonDown("Fire1");

animator.SetFloat("Forward", v);    //파라미터 활성화
animator.SetFloat("Strafe", h);
animator.SetBool("Fire", fire);
}

void OnCollisionEnter(Collision col)
{
if (col.gameObject.CompareTag("Enemy"))
    animator.SetTrigger("Die");
}
*/


/*
//Has Exit Time - 종료 시점(Exit Time)을 활성화 하는 옵션이다.        
활성화
종료 시점이 존재하게 되어 전이의 조건을 만족해도 다음 상태로 전이하지 않게된다. 즉 재생중 에니메이션 종료한 후 전환.
비활성화
전이의 조건을 만족 시, 즉 conditions에 조건이 충족될때 즉시 동작을 전환한다.
*/


// 2D 에니메이션 - SpriteRender

// Multiple Sprite 사용하기
//  텍스쳐 타입으로 Sprite를 선택 후, Sprite Mode를 Multiple로 변경 하고 Sprite Editor 클릭
//  Sprite Editor 로 여러개로 자르기

// Multiple Sprite 애니메이션
//  Window->Animation->Animation으로 Animation 창 열어서 animation을 적용할 GameObject 클릭
//  나눠 놓은 Sprite를 Animation창으로 Drag 하기.


//Animation Layer, Blend Tree   https://minii22.tistory.com/125