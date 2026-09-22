#include "F2837xD_device.h"
#include <math.h>
void clarke_calc(CLARKE_handle v)
{
    v->Valpha = v->AS;
    v->Vbeta  = (v->BS - v->CS) * 0.57735027;
}
void park_calc(PARK_handle v)
{  
   float c,temp;
   if(v->sel)				//角度计算
	{	
		c = sqrt((v->PAlpha * v->PAlpha) + (v->PBeta * v->PBeta));
        temp = 1.0/c;
        v->PCosine = v->PAlpha * temp;
        v->PSine   = v->PBeta * temp;
        v->PDs  = c;
        v->PQs  = 0;
	}
   else
	{
     v->PDs = v->PAlpha * v->PCosine + v->PBeta  * v->PSine ;
	 v->PQs = v->PBeta  * v->PCosine - v->PAlpha * v->PSine ;
	}

}

void ipark_calc(IPARK_handle v)
{
	v->IPAlpha  = v->IPDs * v->IPCosine - v->IPQs * v->IPSine;
	v->IPBeta   = v->IPDs * v->IPSine   + v->IPQs * v->IPCosine;
}

void pid_reg_calc(PIDREG_handle v)
{	
    // Compute the error
    v->Err = v->Ref - v->Fdb;

    if(v->Err > v->ErrMax)// Error Limit
        v->Err = v->ErrMax;
    else if(v->Err < v->ErrMin)
        v->Err = v->ErrMin;

    // Compute the proportional output
    v->Up = v->Kp*v->Err;

    // Compute the integral output
    v->Ui = v->Ui + v->Ki*v->Up ;
    
    // Compute the pre-saturated output
    v->OutPreSat = v->Up + v->Ui ;   
    
    // Saturate the output
    if (v->OutPreSat > v->OutMax)                   
      {
      	v->Out =  v->OutMax;
		v->Ui = v->OutMax - v->Up;
	  }
    else 
      if (v->OutPreSat < v->OutMin)
       {
        v->Out =  v->OutMin;  
		v->Ui = v->OutMin - v->Up;
	   } 
      else
        v->Out = v->OutPreSat;                           
}

void  CurrControl(Curr_handle v)	            //电流内环控制
{
// 这里取测量电流参考方向为网侧流向逆变器的方向为正方向
	v->Vd = v->Vfdbd +  v->Ifdbq * v->wL -v->Vd_Pidout;
	v->Vq = -v->Ifdbd * v->wL - v->Vq_Pidout;
}

void Three_phase_Analyzer(CLARKE_handle Vc,Display_handle Dis,Analyzer_handle Ay)
{
    int i,j,temp;

    temp = Vc->Valpha;
    Ay->Valpha_sum = Ay->Valpha_sum - Ay->Valpha_buf[Ay->V_POS] + temp;
    Ay->Valpha_buf[Ay->V_POS++] = temp;
    if(Ay->V_POS > 15)
        Ay->V_POS=0;

    temp = Dis->Ua + Dis->Ub + Dis->Uc;
    if(temp > 160)
    {

        Ay->Vz_POS &=7;
        Ay->Valpha[Ay->Vz_POS++]=Vc->AS;
        Ay->Samples++;

        j=0;
        for(i=0;i<8;i++)
        {
            if(Ay->Valpha[i]>0)
                j++;
        }
        if(j==4)
        {
            Ay->SampleSum += Ay->Samples;
            Ay->Sample_n++;
            Ay->Samples=0;

            if(Ay->Valpha_sum < -100)//相序判定，正过零点
            {
                if(Vc->Vbeta > 60)
                {
                    Ay->Sequence=0;//逆相序
                }
                else
                    Ay->Sequence=1;//正相序
            }
        }
        if(Ay->Sample_n == 40)//频率计算
        {
            Ay->Freq = 20.0*Ay->Sample_Freq/Ay->SampleSum;
            Ay->SampleSum=0;
            Ay->Sample_n=0;
        }
    }
    else
        Ay->Freq=0;
}

int Grid_Check(GRID_handle grid_para,PARK_handle V_p)
{
	int status=100; 
	int i,temp2;
	float temp;

     temp2 = V_p->PDs * 10.0;
     grid_para->V_sum=grid_para->V_sum+temp2-grid_para->V_grid[grid_para->V_pos];
     grid_para->V_grid[grid_para->V_pos++]= temp2;
     grid_para->V_pos&=15;
     temp=grid_para->V_sum * 0.00625;

     if((temp>400)||(temp<100))    //电压阈值
       grid_para->Err_V++;
     else
       grid_para->Err_V--;

     if(grid_para->Err_V>20)
       grid_para->Err_V=20;
     else if(grid_para->Err_V<0)
       grid_para->Err_V=0;

     i = grid_para->Err_V ;
    if(i>grid_para->Err_norm)   //判断给Err_norm次机会
    {
        status=2;
    }
    else if(i<1)
       status=3;

	return(status);
}

void SVPWM_Mul_Calc(SVPWM_Mul_handle v)
{float Va,Vb,Vc,t1,t2,Re,Im,temp1,temp2,temp3,temp6;
 int Sector=0,Region=0,a[6],Edge=0,temp4,temp5;

    Va = v->Beta;
    Vb = -0.5 * v->Beta + 0.8660254 * v->Alpha;    // 0.8660254 = sqrt(3)/2
    Vc = -0.5 * v->Beta - 0.8660254 * v->Alpha;    // 0.8660254 = sqrt(3)/2

// 60 degree Sign_ determination
    if (Va > 0)
        Sector = 1;
    if (Vb > 0)
        Sector = Sector + 2;
    if (Vc > 0)
        Sector = Sector + 4;

    Edge = v->Sec * 10 + Sector;
    t1 = 0;
    t2 = 0;
    switch (Sector)
    {
    case 1:
        if ((Edge == 31) || (Edge == 51) || (Edge == 11))
        {
            t2 = -Vb;
            t1 = -Vc;
        }
        break;
    case 2:
        if ((Edge == 32) || (Edge == 62) || (Edge == 22))
        {
            t2 = -Vc;
            t1 = -Va;
        }
        break;
    case 3:
        if ((Edge == 23) || (Edge == 13) || (Edge == 33))
        {
            t1 = Vb;
            t2 = Va;
        }
        break;
    case 4:
        if ((Edge == 44) || (Edge == 54) || (Edge == 64))
        {
            t2 = -Va;
            t1 = -Vb;
        }
        break;
    case 5:
        if ((Edge == 15) || (Edge == 45) || (Edge == 55))
        {
            t1 = Va;
            t2 = Vc;
        }
        break;
    case 6:
        if ((Edge == 26) || (Edge == 46) || (Edge == 66))
        {
            t1 = Vc;
            t2 = Vb;
        }
        break;
    default:
        t1 = 0;
        t2 = 0;
        break;
    };

    if (t1 < 0)
        t1 = 0.0000001;
    if (t2 < 0)
        t2 = 0.0000001;
    if ((t1 + t2) > 1.0)
    {
        t1 = t1 / (t1 + t2);
        t2 = 1.0 - t1;
    }

    Re = t1 + t1;
    Im = t2 + t2;
    a[0] = (int) (Re + 1.0);
    a[1] = (int) (Im);
    a[2] = (int) (Re);
    a[3] = (int) (Im + 1.0);
    temp1 = Re + Im;
    temp2 = a[0] + a[1];
    if(temp1 > temp2)
    {
        a[4] = a[0];
        a[5] = a[3];
    }
    else
    {
        a[4] = a[2];
        a[5] = a[1];
    }
    temp4 = a[0] + a[2] + a[4];
    temp5 = a[1] + a[3] + a[5];
    if(temp4 == 2)
        Region = 3;
    else if(temp4 == 4)
        Region = 2;
    else if(temp5 == 1)
        Region = 1;
    else if(temp5 == 4)
        Region = 4;

    Edge = v->Sec * 1000 + Sector * 100 + v->Reg * 10 + Region;
    v->Sec = Sector;
    v->Reg = Region;

    v->Da1 = 0;
    v->Da2 = 1;
    v->Db1 = 0;
    v->Db2 = 1;
    v->Dc1 = 0;
    v->Dc2 = 1;
    v->Pol = 1;

    switch (Region)
    {
    case 1:
        temp1 = Re;
        temp2 = 1.0 - Re - Im;
        temp3 = Im;

        if ((Edge == 1511) || (Edge == 4611) || (Edge == 2311))
        {
            temp6 = temp1 + temp2;
            if (temp6 != 0)
            {
                temp6 = 0.9999999 / temp6;
                temp1 = temp1 * temp6;
                temp2 = temp2 * temp6;
            }
        }
        else if ((Edge == 5111) || (Edge == 6411) || (Edge == 3211))
        {
            temp6 = temp3 + temp2;
            if (temp6 != 0)
            {
                temp6 = 0.9999999 / temp6;
                temp3 = temp3 * temp6;
                temp2 = temp2 * temp6;
            }
        }

        switch (Sector)
        {
        case 3:
            v->Da1 = temp1;
            v->Da2 = 1.0;
            v->Dc1 = 0;
            v->Dc2 = temp2 + temp1;
            v->Db1 = 0;
            v->Db2 = 1.0;
            break;
        case 1:
            v->Db1 = temp3;
            v->Db2 = 1.0;
            v->Dc1 = 0;
            v->Dc2 = temp2 + temp3;
            v->Da1 = 0;
            v->Da2 = 1.0;
            break;
        case 5:
            v->Db1 = temp1;
            v->Db2 = 1.0;
            v->Da1 = 0;
            v->Da2 = temp2 + temp1;
            v->Dc1 = 0;
            v->Dc2 = 1.0;
            break;
        case 4:
            v->Dc1 = temp3;
            v->Dc2 = 1.0;
            v->Da1 = 0;
            v->Da2 = temp2 + temp3;
            v->Db1 = 0;
            v->Db2 = 1.0;
            break;
        case 6:
            v->Dc1 = temp1;
            v->Dc2 = 1.0;
            v->Db1 = 0;
            v->Db2 = temp2 + temp1;
            v->Da1 = 0;
            v->Da2 = 1.0;
            break;
        case 2:
            v->Da1 = temp3;
            v->Da2 = 1.0;
            v->Db1 = 0;
            v->Db2 = temp2 + temp3;
            v->Dc1 = 0;
            v->Dc2 = 1.0;
            break;
        default:
            break;
        }
        break;
    case 2:
        temp1 = 2.0 - Re - Im;
        temp2 = Im;
        temp3 = Re - 1.0;

        if ((Edge == 3332) || (Edge == 5532) || (Edge == 6632))
        {
            temp6 = temp1 + temp2;
            if (temp6 != 0)
            {
                temp6 = 0.9999999 / temp6;
                temp1 = temp1 * temp6;
                temp2 = temp2 * temp6;
            }
        }

        switch (Sector)
        {
        case 3:
            v->Dc1 = 0;
            v->Dc2 = temp1;
            v->Db1 = 0;
            v->Db2 = temp2 + temp1;
            v->Da1 = 1.0;
            v->Da2 = 1.0;
            break;
        case 1:
            v->Da1 = temp3;
            v->Da2 = 1.0;
            v->Db1 = temp2 + temp3;
            v->Db2 = 1.0;
            v->Dc1 = 0;
            v->Dc2 = 0;
            break;
        case 5:
            v->Da1 = 0;
            v->Da2 = temp1;
            v->Dc1 = 0;
            v->Dc2 = temp2 + temp1;
            v->Db1 = 1.0;
            v->Db2 = 1.0;
            break;
        case 4:
            v->Db1 = temp3;
            v->Db2 = 1.0;
            v->Dc1 = temp2 + temp3;
            v->Dc2 = 1.0;
            v->Da1 = 0;
            v->Da2 = 0;
            break;
        case 6:
            v->Db1 = 0;
            v->Db2 = temp1;
            v->Da1 = 0;
            v->Da2 = temp2 + temp1;
            v->Dc1 = 1.0;
            v->Dc2 = 1.0;
            break;
        case 2:
            v->Dc1 = temp3;
            v->Dc2 = 1.0;
            v->Da1 = temp2 + temp3;
            v->Da2 = 1.0;
            v->Db1 = 0;
            v->Db2 = 0;
            break;
        default:
            break;
        }
        break;
    case 3:
        temp1 = 1.0 - Im;
        temp2 = Re + Im - 1.0;
        temp3 = 1.0 - Re;

        if ((Edge == 3323) || (Edge == 5523) || (Edge == 6623))
        {
            temp6 = temp1 + temp2;
            if (temp6 != 0)
            {
                temp6 = 0.9999999 / temp6;
                temp1 = temp1 * temp6;
                temp2 = temp2 * temp6;
            }
        }
        else if ((Edge == 1143) || (Edge == 4443) || (Edge == 2243))
        {
            temp6 = temp3 + temp2;
            if (temp6 != 0)
            {
                temp6 = 0.9999999 / temp6;
                temp3 = temp3 * temp6;
                temp2 = temp2 * temp6;
            }
        }

        switch (Sector)
        {
        case 3:
            v->Dc1 = 0;
            v->Dc2 = temp1;
            v->Da1 = temp2 + temp1;
            v->Da2 = 1.0;
            v->Db1 = 0;
            v->Db2 = 1.0;
            break;
        case 1:
            v->Dc1 = 0;
            v->Dc2 = temp3;
            v->Db1 = temp2 + temp3;
            v->Db2 = 1.0;
            v->Da1 = 0;
            v->Da2 = 1.0;
            break;
        case 5:
            v->Da1 = 0;
            v->Da2 = temp1;
            v->Db1 = temp2 + temp1;
            v->Db2 = 1.0;
            v->Dc1 = 0;
            v->Dc2 = 1.0;
            break;
        case 4:
            v->Da1 = 0;
            v->Da2 = temp3;
            v->Dc1 = temp2 + temp3;
            v->Dc2 = 1.0;
            v->Db1 = 0;
            v->Db2 = 1.0;
            break;
        case 6:
            v->Db1 = 0;
            v->Db2 = temp1;
            v->Dc1 = temp2 + temp1;
            v->Dc2 = 1.0;
            v->Da1 = 0;
            v->Da2 = 1.0;
            break;
        case 2:
            v->Db1 = 0;
            v->Db2 = temp3;
            v->Da1 = temp2 + temp3;
            v->Da2 = 1.0;
            v->Dc1 = 0;
            v->Dc2 = 1.0;
            break;
        default:
            break;
        }
        break;
    case 4:
        temp1 = 2.0 - Re - Im;
        temp2 = Re;
        temp3 = Im - 1.0;

        if ((Edge == 1134) || (Edge == 4434) || (Edge == 2234))
        {
            temp6 = temp1 + temp2;
            if (temp6 != 0)
            {
                temp6 = 0.9999999 / temp6;
                temp1 = temp1 * temp6;
                temp2 = temp2 * temp6;
            }
        }

        switch (Sector)
        {
        case 3:
            v->Db1 = temp3;
            v->Db2 = 1.0;
            v->Da1 = temp2 + temp3;
            v->Da2 = 1.0;
            v->Dc1 = 0;
            v->Dc2 = 0;
            break;
        case 1:
            v->Dc1 = 0;
            v->Dc2 = temp1;
            v->Da1 = 0;
            v->Da2 = temp2 + temp1;
            v->Db1 = 1.0;
            v->Db2 = 1.0;
            break;
        case 5:
            v->Dc1 = temp3;
            v->Dc2 = 1.0;
            v->Db1 = temp2 + temp3;
            v->Db2 = 1.0;
            v->Da1 = 0;
            v->Da2 = 0;
            break;
        case 4:
            v->Da1 = 0;
            v->Da2 = temp1;
            v->Db1 = 0;
            v->Db2 = temp2 + temp1;
            v->Dc1 = 1.0;
            v->Dc2 = 1.0;
            break;
        case 6:
            v->Da1 = temp3;
            v->Da2 = 1.0;
            v->Dc1 = temp2 + temp3;
            v->Dc2 = 1.0;
            v->Db1 = 0;
            v->Db2 = 0;
            break;
        case 2:
            v->Db1 = 0;
            v->Db2 = temp1;
            v->Dc1 = 0;
            v->Dc2 = temp2 + temp1;
            v->Da1 = 1.0;
            v->Da2 = 1.0;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
