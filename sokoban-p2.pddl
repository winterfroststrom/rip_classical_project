(define (problem sokoban-p2)
  (:domain sokoban-domain)
  (:objects b11 b12 b13 b21 b22 b23 b24 b32 b33 b34 b43 b44 b54 b64)
  (:init (player_at b21) (box_at b22) (box_at b23) 
	(adj b11 b12) (adj b12 b11) 
	(adj b12 b13) (adj b13 b12) 

	(adj b21 b22) (adj b22 b21) 
	(adj b22 b23) (adj b23 b22) 
	(adj b23 b24) (adj b24 b23) 

	(adj b32 b33) (adj b33 b32) 
	(adj b33 b34) (adj b34 b33) 

	(adj b43 b44) (adj b44 b43) 

	(adj b11 b21) (adj b21 b11) 
	(adj b12 b22) (adj b22 b12) 
	(adj b13 b23) (adj b23 b13) 

	(adj b22 b32) (adj b32 b22) 
	(adj b23 b33) (adj b33 b23) 
	(adj b24 b34) (adj b34 b24) 

	(adj b33 b43) (adj b43 b33) 
	(adj b34 b44) (adj b44 b34) 

	(adj b44 b54) (adj b54 b44) 
	(adj b54 b64) (adj b64 b54) 

	(pushable b11 b13) (pushable b13 b11) ;b12

	(pushable b12 b32) (pushable b32 b12) ;b22
	(pushable b21 b23) (pushable b23 b21)
	
	(pushable b13 b33) (pushable b33 b13) ;b23
	(pushable b22 b24) (pushable b24 b22)

	(pushable b23 b43) (pushable b43 b23) ;b33
	(pushable b32 b34) (pushable b34 b32)

	(pushable b24 b44) (pushable b44 b24) ;b34

	(pushable b34 b54) (pushable b54 b34) ;b44

	(pushable b44 b64) (pushable b64 b44);b54
	)
  (:goal (and (box_at b11)
              (box_at b64)))
)
