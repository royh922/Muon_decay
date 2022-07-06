import numpy as np

def dE_dx_in_air(KE,m_proj,z_proj,altitude):
    """
    This is a speicalized energy loss function that determines
    the energy loss of a charged projectile in air. It uses the
    Bethe Bloch formula with shell and density correction terms.
    The user enters the KE of the projectile in MeV, the mass of
    the projectile in MeV, the magnitude of the charge of the
    projectile in multiples of the elementary charge, and the
    altitude of the projectile in meters. The altitude is needed
    because this function calculates the density of air as a function
    of the altitude
    """
    N_a = 6.022E23 # mol^-1
    r_e = 2.817E-13 # cm
    m_e_c2 = 0.511 # MeV
    Z_abs = 14.83
    A_abs = 29.72 # g/mol
    gamma = (KE + m_proj)/m_proj
    beta = np.sqrt(1- 1/gamma**2)
    eta = gamma*beta
    s = m_e_c2 / m_proj
    W_max = (2*m_e_c2*eta**2)/(1+2*s*np.sqrt(1+eta**2)+s**2) # MeV
    I = 85.7 # eV
   
    # Calculate the density
    rho_0 = 1.205E-3 # density at 1 atm and 20 Celsius
    mass_of_one = (A_abs / N_a)/1000 # in kg
    g = 9.8 # m/s^2
    K = 1.38065E-23 # J/K
    T = 293.15 # 20 Celsius in Kelvin
    rho = rho_0 * np.exp(-1*mass_of_one*g*altitude / (K*T) )
    first_factor = 2 * np.pi * N_a * r_e**2 * m_e_c2 * rho
    first_factor = first_factor * (Z_abs*z_proj**2) / (A_abs * beta**2)
    print("The first factor is {:.8g}".format(first_factor))
    arg_of_ln = 2*m_e_c2*((gamma*beta)**2)*W_max/((1E-6*I)**2)
    print("The ln term is {:.5g}".format(np.log(arg_of_ln)))
   
    # Shell correction for high energies
    X_0 = 1.742
    X_1 = 4.28
    a = 0.1091
    m = 3.40
    X = np.log10(gamma*beta)
    # Calculate the C_0 constant
    N_e = N_a * rho * Z_abs / A_abs
    nu_p = np.sqrt(80.617E6 * N_e)  # where e^2 / (pi * m_e)
    h = 4.13567E-15 # eV s
    C_0 = -1 * (2 * np.log(1/(h*nu_p))+1)
   
    if (X > X_1):
        delta = 4.6052 + C_0
    else:
        if (X > X_0):
            delta = 4.6052 * X + C_0 + a * (X_1 - X)**m
        else:
            delta = 0
           
    C = (0.422377 * eta**-2 + 0.0304043 * eta**-4 + 0.00038106 * eta**-6) * 1E-6 * I*I
    C = C + (3.850190*eta**-2 - 0.1667989*eta**-4 + 0.00157955*eta**-6) * 1E-9 * I**3
   
    result = first_factor * ( np.log(arg_of_ln) - 2*beta**2 - delta- 2*C/Z_abs)
    return result

m_proj = 105.6 # MeV
gamma_proj = 58
# KE = gamma_proj*m_proj - m_proj
KE = 2016.648345817
z_proj = 1
altitude = 15000

energy_loss = dE_dx_in_air(KE, m_proj, z_proj, altitude)
print(energy_loss)