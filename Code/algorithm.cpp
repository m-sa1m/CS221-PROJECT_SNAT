// 5) RISK CALCULATION ALGORITHM
int calculateRisk(System* sys) {
    int score = 0;
    
    // Password risk (weaker = higher risk)
    score += (10 - sys->passwordStrength) * 3;
    
    // Open ports risk
    score += sys->openPorts * 8;
    
    // Firewall risk
    if(!sys->firewallOn) score += 25;
    
    sys->riskScore = (score > 100) ? 100 : score;
    return sys->riskScore;
}
