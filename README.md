# Head-Tracker-Binaural-Sound


IDEE:
Die Idee war es, ein realistisches Höhrerlebnis trotz der Benutzung von Kopfhörer zu erzeugen. Generell ist es 
beim tragen von Kopfhörern so, dass der Klang nur von links und rechts die Ohren beschallt. 
Die Rotation des Kopfes, oder der Abstand zu Schallquelle hat somit im Vergleich zu echten Lautsprechern in 
einer Stereokonfiguration die in einem Winkel (ca.60 Grad) vor dem Höhrer platziert, keinen Einfluss. 

Umsetzung:

Um das Projekt zu realisieren haben wir, mit Hilfe eines Laptops und Webcam, das Gesicht aufgenommen. 
Innerhalb Openframeworks haben wir die Daten der Kamera verarbeitet, also die Bewegungen des Kopfes getrack. 
Mittels eines Schwerpunkt innerhalb des Gesichts, in unserem Fall die Nase, konnten wir die x, y Position tracken. 
Durch die Positionierung von zwei weiteren Punkten (Kiefer links und rechts) konnte der Abstand zum Bildschirm detektiert werden, 
da sich der Abstand der zwei Punkte je nach Abstand zum Bildschirm verändert. Diese Daten wurden im Anschluss mit OSC (Open Sound Control) 
an das Audioverarbeitungsproramm Reaper gesendet.

Reaper hat ebenfalls eine OSC Schnittstelle mit der wir zwischen Openframeworks und Reaper eine Verbindung aufbauen konnten.

Die oben genannten Parameter haben dann das Sennheiser Ambeo Plug In gesteuert. 

