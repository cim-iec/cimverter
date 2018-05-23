- powersystems_slack_load_line_sample_reference
  - dymola: kompiliert + simuliert + Ergebnis korrekt
  - om: kompiliert NICHT ("Das Modell ist strukturell singulär")

- powersystems_slack_trafo_load_sample_reference
  - dymola: kompiliert nicht ("Scalar system is always singular")
  - om: kompiliert NICHT ("Das Modell ist strukturell singulär")

- powersystems_slack_trafo_load_ground_sample_reference
  - dymola: kompiliert + simuliert + Ergebnis korrekt
  - om: kompiliert + simuliert, Ergebnis ABWEICHEND

- powersystems_slack_load_line_ground_sample_reference
  - dymola: kompiliert + simuliert + Ergebnis korrekt
  - om: kompiliert + simuliert, Ergebnis FALSCH
