# Calculate error vector
e_ = self.target.r_ - self.missile.r_

if self.t > self.missile.guidance_delay:
    prev_e_ = np.array([0,0,0])

    # e_ will converge to the vector pointing to the eventual collision location
    while np.linalg.norm(e_) - np.linalg.norm(prev_e_) > 1.0:
        prev_e_ = e_
        ete_impact = np.linalg.norm(e_) / np.dot(self.missile.v_, normalize(e_))
        target_r_impact_ = self.target.r_ + self.target.v_ * ete_impact                
        e_ = target_r_impact_ - self.missile.r_

    # Offset the velocity perpendicular to e_ to prevent drifting
    dir_ = normalize(e_)
    perp_v_ = self.missile.v_ - np.dot(self.missile.v_, dir_) * dir_
    e_ = e_ - perp_v_ * np.linalg.norm(e_) / np.linalg.norm(self.missile.v_
