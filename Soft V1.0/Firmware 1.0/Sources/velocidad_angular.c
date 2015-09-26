#include "velocidad_angular.h"

/** \file velocidad_angular.c */

/** \def WHEEL_RADIUS
 * \brief Radio de las ruedas del robot en mil&iacute;metros.
 * \hideinitializer */
#define WHEEL_RADIUS 37


/** \def HALF_WHEEL_DISTANCE
 * \brief Mitad de la distancia entre las ruedas del robot mil&iacute;metros.
 * \hideinitializer */
#define HALF_WHEEL_DISTANCE 64

#define MAX_LEFT_WHEEL_PWM  100
#define MAX_RIGHT_WHEEL_PWM 100

#define MIN_LEFT_WHEEL_PWM 10
#define MIN_RIGHT_WHEEL_PWM 10


#define THRESHOLD_LEFT_WHEEL_PWM    1
#define THRESHOLD_RIGHT_WHEEL_PWM   1 

#define MAX_TANGENTIAL_SPEED 120

/** \def MAX_WHEEL_ANGULAR_SPEED
 * \brief M&aacute;xima velocidad angular de los motores en miliradianes por
 * segundo.
 * \hideinitializer
 *
 * Si n es la cantidad de vueltas por segundo que pueden lograr los motores
 * entonces MAX_WHEEL_ANGULAR_SPEED se define como \f$2*\pi*n*1000\f$. Se
 * debe usar la m&aacute;xima velocidad real, no la nominal. */
#define MAX_WHEEL_ANGULAR_SPEED ((int32_t)MAX_TANGENTIAL_SPEED*1000/WHEEL_RADIUS)


/// \cond
#define ABS( x ) ( ( ( x ) < 0 ) ? -( x ) : ( x ) )
/// \endcond

//----------------------------------------------------------------
//
//                      Funciones privadas
//
//----------------------------------------------------------------

/**
 * \brief Convierte velocidad tangencial y angular del robot en velocidad
 * angular de las ruedas.
 * \param tangential_speed Velocidad tangencial del robot expresada en [mm/s]
 * \param angular_speed Velocidad angular del robot expresada en [mrad/s].
 * Ej: PI[rad/s] = 3142[mrad/s]
 * \param left_wheel_angular_speed Puntero a la direcci&oacute;n donde se
 * devolver&aacute; la velocidad angular de la rueda izquierda
 * \param right_wheel_angular_speed Puntero a la direcci&oacute;n donde se
 * devolver&aacute; la velocidad angular de la rueda derecha
 */
static void _robot_speed_to_wheel_speed(
    /* parametros */
    int tangential_speed,
    int angular_speed,
    int32_t *left_wheel_angular_speed,
    int32_t *right_wheel_angular_speed ) {

    /* variables */
    /* velocidad angular de una rueda hipotetica ubicada en el centro del
     * robot */
    int32_t mw_ang_speed;

    mw_ang_speed    = tangential_speed  * 1000  / WHEEL_RADIUS; /* [mrad/s] */
    *left_wheel_angular_speed   = mw_ang_speed  + (angular_speed     * HALF_WHEEL_DISTANCE  + ( WHEEL_RADIUS    >> 1 ) )  / WHEEL_RADIUS; /* [mrad/s] */
    *right_wheel_angular_speed  = mw_ang_speed  - (angular_speed     * HALF_WHEEL_DISTANCE  + ( WHEEL_RADIUS    >> 1 ) )  / WHEEL_RADIUS; /* [mrad/s] */
}
/**
 * \brief Convierte la velocidad angular de las ruedas a valores PWM.
 * \return Retorna un valor negativo si hay un error. Si no, el bit menos
 * significativo representa el sentido del giro de la rueda izquierda y el
 * segundo menos significativo representa el sentido la rueda derecha. En
 * ambos casos, 0 significa hacia adelante y uno hacia atr&aacute;s. */
static int _wheel_speed_to_pwm(
    /* parametros */
    int32_t left_wheel_angular_speed,
    int32_t right_wheel_angular_speed,
    uint8_t *left_wheel_pwm,
    uint8_t *right_wheel_pwm ) {

    /* variables */
    int sentidos    = 0;

    int32_t lw_pwm;
    int32_t rw_pwm;


    lw_pwm  =   ( ( ABS( left_wheel_angular_speed )   * MAX_LEFT_WHEEL_PWM  + ( MAX_WHEEL_ANGULAR_SPEED >> 1 ) )   / MAX_WHEEL_ANGULAR_SPEED );
    rw_pwm  =   ( ( ABS( right_wheel_angular_speed )  * MAX_RIGHT_WHEEL_PWM + ( MAX_WHEEL_ANGULAR_SPEED >> 1 ) )   / MAX_WHEEL_ANGULAR_SPEED );

    /* si la velocidad de alguna de las ruedas es mayor que la maxima,
     * reducir ambas velocidades manteniendo la relacion */
    if( lw_pwm  > MAX_LEFT_WHEEL_PWM ) {
        rw_pwm  = ( rw_pwm     * MAX_LEFT_WHEEL_PWM     + ( lw_pwm  >> 1 ) )    / lw_pwm;
        lw_pwm  = MAX_LEFT_WHEEL_PWM;
    }
    if( rw_pwm  > MAX_RIGHT_WHEEL_PWM ) {
        lw_pwm  = ( lw_pwm     * MAX_RIGHT_WHEEL_PWM    + ( rw_pwm  >> 1 ) )    / rw_pwm;
        rw_pwm  = MAX_RIGHT_WHEEL_PWM;
    }

    /* si la velocidad de la rueda izquierda */
    if( lw_pwm  < THRESHOLD_LEFT_WHEEL_PWM ) {
        lw_pwm = 0;
    /* si la velocidad de la rueda izquierda es menor que la minima,
     * aumentar ambas velocidades manteniendo la relacion */
    } else if( lw_pwm  < MIN_LEFT_WHEEL_PWM ) {
        rw_pwm  = ( rw_pwm     * MIN_LEFT_WHEEL_PWM     + ( lw_pwm >> 1 ) )     / lw_pwm;
        if( rw_pwm  > MAX_RIGHT_WHEEL_PWM )
            rw_pwm  = MAX_RIGHT_WHEEL_PWM;
        lw_pwm  = MIN_LEFT_WHEEL_PWM;
    }

    if( rw_pwm  < THRESHOLD_RIGHT_WHEEL_PWM ) {
        rw_pwm = 0;
    } else if( rw_pwm  < MIN_RIGHT_WHEEL_PWM ) {
        lw_pwm  = ( lw_pwm     * MIN_RIGHT_WHEEL_PWM    + ( rw_pwm  >> 1 ) )    / rw_pwm;
        if( lw_pwm  > MAX_LEFT_WHEEL_PWM )
            lw_pwm  = MAX_LEFT_WHEEL_PWM;
        rw_pwm  = MIN_RIGHT_WHEEL_PWM;
    }

    *left_wheel_pwm = lw_pwm;
    *right_wheel_pwm = rw_pwm;

    /* determinar el sentido del giro */
    if( left_wheel_angular_speed    < 0 )
        sentidos    |= 0x01;
    if( right_wheel_angular_speed   < 0 )
        sentidos    |= 0x02;

    return sentidos;
}



//----------------------------------------------------------------
//
//                      Funciones publicas
//
//----------------------------------------------------------------

/**
 * \brief Convierte velocidad tangencial y angular del robot en valores PWM.
 * \param tangential_speed Velocidad tangencial del robot en [mm/s].
 * \param angular_speed Velocidad angular del robot en [mrad/s].
 * \param left_wheel_pwm Puntero a la direcci&oacute;n donde se
 * devolver&aacute; el valor PWM para la rueda izquierda.
 * \param right_wheel_pwm Puntero a la direcci&oacute;n donde se
 * devolver&aacute; el valor PWM para la rueda derecha.
 * \return Retorna un valor negativo si hay un error. Si no, el bit menos significativo
 * representa el sentido del giro de la rueda izquierda y el segundo menos significativo
 * representa el sentido la rueda derecha. En ambos casos, 0 significa hacia
 * adelante y uno hacia atr&aacute;s.
 *
 * Si la velocidad deseada no es soportada por los motores, entonces se
 * preserva el radio de giro, reduciendo la velocidad de ambas ruedas
 * proporcionalmente. */
int robot_speed_to_pwm(
    /* parametros */
    int tangential_speed,
    int angular_speed,
    uint8_t *left_wheel_pwm,
    uint8_t *right_wheel_pwm ) {

    /* variables */
    int32_t lw_angular_speed = 0;
    int32_t rw_angular_speed = 0;

    /* transformar velocidades tangencial y angular del robot, en velocidades angulares de las ruedas */
    _robot_speed_to_wheel_speed( tangential_speed, angular_speed, &lw_angular_speed, &rw_angular_speed );

    /* transforamar velocidades angulares de las ruedas en pwm */
    return _wheel_speed_to_pwm( lw_angular_speed, rw_angular_speed, left_wheel_pwm, right_wheel_pwm );

}
