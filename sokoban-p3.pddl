(define (problem sokoban-p3)
  (:domain sokoban-domain)
  (:objects b17 b18 b19 b27 b29 b37 b39 b41 b42 b43 b44 b45 b46 b47 b48 b49 b51 b53 b55 b57 b61 b62 b63 b64 b65 b66 b67)
  (:init (player_at b42) (box_at b44) (box_at b46) (box_at b48) (adj b17 b18) (adj b18 b17) (adj b18 b19) (adj b19 b18) (adj b41 b42) (adj b42 b41) (adj b42 b43) (adj b43 b42) (adj b43 b44) (adj b44 b43) (adj b44 b45) (adj b45 b44) (adj b45 b46) (adj b46 b45) (adj b46 b47) (adj b47 b46) (adj b47 b48) (adj b48 b47) (adj b48 b49) (adj b49 b48) (adj b61 b62) (adj b62 b61) (adj b62 b63) (adj b63 b62) (adj b63 b64) (adj b64 b63) (adj b64 b65) (adj b65 b64) (adj b65 b66) (adj b66 b65) (adj b66 b67) (adj b67 b66) (adj b17 b27) (adj b27 b17) (adj b27 37) (adj b37 b27) (adj b37 b47) (adj b47 b37) (adj b47 b57) (adj b57 b47) (adj b57 b67) (adj b67 b57) (adj b19 b29) (adj b29 b19) (adj b29 b39) (adj b39 b29) (adj b39 b49) (adj b49 b39) (adj b41 b51) (adj b51 b41) (adj b51 b61) (adj b61 b51) (adj b43 b53) (adj b53 b43) (adj b53 b63) (adj b63 b53) (adj b45 b55) (adj b55 b45) (adj b55 b65) (adj b65 b55) (pushable b17 b19) (pushable b41 b43) (pushable b43 b41) (pushable b42 b44) (pushable b44 b42) (pushable b43 b45) (pushable b45 b43) (pushable b44 b46) (pushable b46 b44) (pushable b45 b47) (pushable b47 b45) (pushable b46 b48) (pushable b48 b46) (pushable b47 b49) (pushable b49 b47) (pushable b61 b63) (pushable b63 b61) (pushable b62 b64) (pushable b64 b62) (pushable b63 b65) (pushable b65 b63) (pushable b64 b66) (pushable b66 b64) (pushable b65 b67) (pushable b67 b65) (pushable b41 b61) (pushable b61 b41) (pushable b43 b63) (pushable b63 b43) (pushable b45 b65) (pushable b65 b45) (pushable b17 b37) (pushable b37 b17) (pushable b27 b47) (pushable b47 b27) (pushable b37 b57) (pushable b57 b37) (pushable b47 b67) (pushable b67 b47) (pushable b19 b39) (pushable b39 b19) (pushable b29 b49) (pushable b49 b29))
  (:goal (and (box_at b17)
	      (box_at b27)
	      (box_at b37)))
)